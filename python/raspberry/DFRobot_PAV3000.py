# -*- coding: utf-8 -*
'''!
    @file        DFRobot_PAV3000.py
    @brief       This is the air velocity module driver library.
    @copyright   Copyright (c) 2024 DFRobot Co.Ltd (http://www.dfrobot.com)
    @license     The MIT License (MIT)
    @author      TangJie(jie.tang@dfrobot.com)
    @version     V1.0
    @date        2024-12-02
    @url         https://github.com/DFRobot/DFRobot_PAV3000
'''
import time
import smbus2
from smbus2 import i2c_msg

AIRFLOW_RANGE_7_MPS = 9
AIRFLOW_RANGE_15_MPS = 13

class DFRobot_PAV3000:

    def __init__(self):
        self._addr = 0x28
        self.i2c = smbus2.SMBus(1)
        self._range = 0
        self._mpsDataPoint = [0] * 14
        self._rawDataPoint = [0] * 14
        self.mpsDataPoint_7_mps = [0, 1.07, 2.01, 3.00, 3.97, 4.96, 5.98, 6.99, 7.23]
        self.rawDataPoint_7_mps = [409, 915, 1522, 2066, 2523, 2908, 3256, 3572, 3686]
        self.mpsDataPoint_15_mps = [0, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 11.00, 13.00, 15.00]
        self.rawDataPoint_15_mps =  [409, 1203, 1597, 1908, 2187, 2400, 2629, 2801, 3006, 3178, 3309, 3563, 3686]


    def set_range(self, range):
        '''
            @fn set_range
            @brief Set the airflow detection range.
            @range AIRFLOW_RANGE_7_MPS: PAV3000_1005, AIRFLOW_RANGE_15MPS: PAV3000_1015
        '''
        self._range = range
        
        if self._range == AIRFLOW_RANGE_7_MPS:
            self._mpsDataPoint = list(self.mpsDataPoint_7_mps)
            self._rawDataPoint = list(self.rawDataPoint_7_mps)
        elif self._range == AIRFLOW_RANGE_15_MPS:
            self._mpsDataPoint = list(self.mpsDataPoint_15_mps)
            self._rawDataPoint = list(self.rawDataPoint_15_mps)

    def read_raw(self):
        '''
            @fn read_raw
            @brief Get the raw data from the sensor.
            @return Raw data from the PAV3000 register.
        '''
        self.ret = 0
        readBuf = self._read_data()
        if self._check_sum(readBuf):
            self.ret = readBuf[1] << 8 | readBuf[2]
        return self.ret
    
    def read_meter_per_sec(self):
        '''
            @fn read_meter_per_sec
            @brief Get the airflow velocity in meters per second (m/s).
            @return Airflow velocity data.
        '''
        self.data_position = 0
        self.air_flow_raw = self.read_raw()

        if (self.air_flow_raw < 409):
            return 0
        elif (self.air_flow_raw >= 3686):
            if self._range == AIRFLOW_RANGE_7_MPS:
                return 7.23
            elif self._range == AIRFLOW_RANGE_15_MPS:
                return 15.00
        
        for i in range(self._range):
            if (self.air_flow_raw > self._rawDataPoint[i]):
                self.data_position = i

        self.window_size = self._rawDataPoint[self.data_position+1] - self._rawDataPoint[self.data_position]
        self.diff = self.air_flow_raw  - self._rawDataPoint[self.data_position]
        self.percentage_of_window = float(self.diff) / float(self.window_size)
        self.window_size_mps = self._mpsDataPoint[self.data_position+1] - self._mpsDataPoint[self.data_position]

        self.air_flow_mps = self._mpsDataPoint[self.data_position] + (self.window_size_mps * self.percentage_of_window)

        return round(self.air_flow_mps, 2)
    
    def read_mile_per_hour(self):
        '''
            @fn read_mile_per_hour
            @brief Get the airflow velocity in miles per hour (mph).
            @return Airflow velocity data.
        '''
        return round((self.read_meter_per_sec() * 2.2369362912), 2)


    def _check_sum(self,buf):
        self.sum = 0
        for i in range(0, 5):
            self.sum += buf[i]
        if (self.sum & 0xff) == 0:
            return True
        return False

    def i2c_read_without_refister(self,address, len):
      read_msg = i2c_msg.read(address,len)
      self.i2c.i2c_rdwr(read_msg)
      return list(read_msg)

    def _read_data(self):
        rslt = self.i2c_read_without_refister(self._addr, 5)
        time.sleep(0.1)
        return rslt