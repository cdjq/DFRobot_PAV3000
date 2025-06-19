/**
 * @file DFRobot_PAV3000.h
 * @brief This is the constructor for the air velocity module driver library.
 * @copyright Copyright (c) 2024 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author    [TangJie](jie.tang@dfrobot.com)
 * @version   V1.0
 * @date      2024-12-02
 * @url https://github.com/DFRobot/DFRobot_PAV3000
 */

#ifndef _DFROBOT_PAV3000_
#define _DFROBOT_PAV3000_

#include "Arduino.h"
#include "Wire.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define AIRFLOW_RANGE_7_MPS 0x09
#define AIRFLOW_RANGE_15_MPS 0x0D

//#define ENABLE_DBG ///< Enable this macro to view the detailed execution process of the program.
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

class DFRobot_PAV3000
{
public:
    /**
     * @fn DFRobot_PAV3000
     * @brief Constructor for the PAV3000 sensor.
     * @param pWire I2C bus object.
     * @return NULL
     */
    DFRobot_PAV3000(TwoWire *pWire=&Wire);

    /**
     * @fn ~DFRobot_PAV3000
     * @brief Destructor for the PAV3000 sensor.
     */
    ~DFRobot_PAV3000(void){
        _pWire->end();
    };

    /**
     * @fn setRange
     * @brief Set the airflow detection range.
     * @param range AIRFLOW_RANGE_7_MPS: PAV3000_1005, AIRFLOW_RANGE_15MPS: PAV3000_1015
     * @return 1: Setting successful, 0: Setting failed.
     */
    uint8_t setRange(uint8_t range);

    /**
     * @fn readRaw
     * @brief Get the raw data from the sensor.
     * @return Raw data from the PAV3000 register.
     */
    uint16_t readRaw(void);

    /**
     * @fn readMeterPerSec
     * @brief Get the airflow velocity in meters per second (m/s).
     * @return Airflow velocity data.
     */
    float readMeterPerSec(void);

    /**
     * @fn readMilePerHour
     * @brief Get the airflow velocity in miles per hour (mph).
     * @return Airflow velocity data.
     */
    float readMilePerHour(void);


private:
    TwoWire *_pWire;

    uint8_t readData(void* buf, uint8_t len);
    bool checkSum(void* buf);
    float _mpsDataPoint[13]; 
    int _rawDataPoint[13]; 
    uint8_t _addr = 0x28;


};

#endif
