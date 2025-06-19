/**
 * @file DFRobot_PAV3000.h
 * @brief This is the implementation of the air velocity module driver library.
 * @copyright Copyright (c) 2024 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author    [TangJie](jie.tang@dfrobot.com)
 * @version   V1.0
 * @date      2024-12-02
 * @url https://github.com/DFRobot/DFRobot_PAV3000
 */

#include "DFRobot_PAV3000.h"
static uint8_t _range = 0;

DFRobot_PAV3000::DFRobot_PAV3000(TwoWire *pWire):_pWire(pWire){}


uint8_t DFRobot_PAV3000::setRange(uint8_t range)
{
    _range = range;
    float mpsDataPoint_7_mps[9] = {0, 1.07, 2.01, 3.00, 3.97, 4.96, 5.98, 6.99, 7.23}; // PAV3000-1005 datapoints
    int rawDataPoint_7_mps[9] =  {409, 915, 1522, 2066, 2523, 2908, 3256, 3572, 3686}; // PAV3000-1005 datapoints
    float mpsDataPoint_15_mps[13] = {0, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 11.00, 13.00, 15.00}; // PAV3000-1015 datapoints
    int rawDataPoint_15_mps[13] =  {409, 1203, 1597, 1908, 2187, 2400, 2629, 2801, 3006, 3178, 3309, 3563, 3686}; // PAV3000-1015 datapoints

    _pWire->begin();
    _pWire->beginTransmission(_addr);

    if(_pWire->endTransmission() != 0){
        return 0;
    }
    
    if(_range == AIRFLOW_RANGE_7_MPS)
    {
        memcpy(_mpsDataPoint,mpsDataPoint_7_mps,sizeof(float) * _range);
        memcpy(_rawDataPoint,rawDataPoint_7_mps,sizeof(int) * _range);
    }

    if(_range == AIRFLOW_RANGE_15_MPS)
    {
        memcpy(_mpsDataPoint,mpsDataPoint_15_mps,sizeof(float) * _range);
        memcpy(_rawDataPoint,rawDataPoint_15_mps,sizeof(int) * _range);
    }

    return 1;
} 


uint16_t DFRobot_PAV3000::readRaw(void)
{
    uint8_t readBuf[5];
    uint16_t ret = 0;

    if(readData(readBuf, 5) == 5)
    {
        if(checkSum(readBuf))
        {
            ret = readBuf[1] << 8 | readBuf[2];
        }
    }

    return ret; 
}

float DFRobot_PAV3000::readMeterPerSec(void)
{
    uint16_t airflowRaw = readRaw();
    int data_position = 0;
    float airflowMps = 0.0;
    
    if(airflowRaw < 409){
        return 0.0;
    }else if(airflowRaw >= 3686)
    {   
        if(_range == AIRFLOW_RANGE_7_MPS)
        {
            return 7.23;
        }
        else if(_range == AIRFLOW_RANGE_15_MPS)
        {
            return 15.00;
        }
    }

    for( int i = 0 ; i < _range ; i++) 
    {
        if (airflowRaw > (uint16_t)_rawDataPoint[i])
        {
          data_position = i;
        }
    }
    int window_size = (_rawDataPoint[data_position+1] - _rawDataPoint[data_position]);
    int diff = (airflowRaw - _rawDataPoint[data_position]);
    float percentage_of_window = ((float)diff / (float)window_size);
    float window_size_mps = (_mpsDataPoint[data_position+1] - _mpsDataPoint[data_position]);
    airflowMps = _mpsDataPoint[data_position] + (window_size_mps*percentage_of_window);

    return airflowMps;

}

float DFRobot_PAV3000::readMilePerHour(void)
{
    return (readMeterPerSec() * 2.2369362912);
}


uint8_t DFRobot_PAV3000::readData(void* buf,  uint8_t len)
{
    uint8_t *_buf = (uint8_t*)buf;
    uint8_t ret = _pWire->requestFrom(_addr, len);

    for(uint8_t i = 0; i < len; i++)
    {
        _buf[i] = _pWire->read();
    }

    return ret;
}

bool DFRobot_PAV3000::checkSum(void* buf)
{
    uint8_t* _buf = (uint8_t*)buf;
    uint16_t sum = 0;

    for(uint8_t i = 0; i < 5; i++){
        sum += _buf[i];
    }

    if((sum  & 0xff)== 0){
        DBG("check sum ok");
        return true;
    }

    DBG("check sum error");
    return false;
}
