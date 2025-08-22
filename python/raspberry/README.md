DFRobot_PAV3000
===========================

- [中文版](./README_CN.md)

This is a driver library for an air velocity sensor.

![Product Effect Image](../../resources/images/SEN0501.png)
![Product Effect Image](../../resources/images/SEN0500.png)

## Product Link (https://www.dfrobot.com)

    SKU：NULL

## Table of Contents

  * [summary](#summary)
  * [installation](#installation)
  * [methods](#methods)
  * [compatibility](#compatibility)
  * [history](#history)
  * [credits](#credits)

## Summary

This is a driver library for an air velocity sensor.

## Installation

Download this library to Raspberry Pi before use, then open the routine folder. Type python demox.py on the command line to execute a routine demox.py. For example, to execute the control_led.py routine, you need to enter:

```python
python PAV3000.py
```

## Methods

```python
    def set_range(self, range):
        '''
            @fn set_range
            @brief Set the airflow detection range and initialize calibration data.
            @details This function configures the sensor for either 7 m/s or 15 m/s range.
                     It loads the appropriate calibration data points for linear interpolation.
                     The calibration data consists of raw ADC values and corresponding 
                     velocity measurements at specific points.
            @param range AIRFLOW_RANGE_7_MPS: PAV3000_1005 (0-7.23 m/s), 
                         AIRFLOW_RANGE_15MPS: PAV3000_1015 (0-15 m/s)
            @return 1: Setting successful, 0: Setting failed (I2C communication error)
        '''

    def read_raw(self):
        '''
            @fn read_raw
            @brief Get the raw data from the sensor.
            @return Raw data from the PAV3000 register.
        '''
    
    def read_meter_per_sec(self):
        '''
            @fn read_meter_per_sec
            @brief Get the airflow velocity in meters per second using linear interpolation.
            @details This function implements a linear interpolation algorithm to convert
                     raw ADC values to velocity measurements. The algorithm works as follows:
                     1. Read raw ADC value from sensor
                     2. Check if value is within valid range (409-3686)
                     3. Find the calibration data points that bracket the raw value
                     4. Calculate the percentage position within the bracket
                     5. Apply linear interpolation: velocity = v1 + (v2-v1) * percentage
            @return Airflow velocity in m/s, or 0.0 if sensor reading is invalid
        '''
    
    def read_mile_per_hour(self):
        '''
            @fn read_mile_per_hour
            @brief Get the airflow velocity in miles per hour (mph).
            @return Airflow velocity data.
        '''
```

## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| Raspberry Pi2 |           |            |    √     |         |
| Raspberry Pi3 |           |            |    √     |         |
| Raspberry Pi4 |       √   |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |

## History

- 2021-08-31 - Version 1.0.0 released.

## Credits

Written by TangJie(jie.tang@dfrobot.com), 2025. (Welcome to our [website](https://www.dfrobot.com/))
