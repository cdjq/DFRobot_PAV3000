DFRobot_PAV3000
===========================

* [中文版](./README_CN.md)

This is a driver library for an air velocity sensor.

![Product Effect Image](./resources/images/SEN0501.png)
![Product Effect Image](./resources/images/SEN0500.png)
  
## Product Link (https://www.dfrobot.com)
    SKU: NULL

## Table of Contents

  * [Summary](#summary)
  * [Installation](#installation)
  * [Methods](#methods)
  * [Compatibility](#compatibility)
  * [History](#history)
  * [Credits](#credits)

## Summary

This is a driver library for an air velocity sensor.


## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
    /**
     * @fn setRange
     * @brief Set the airflow detection range and initialize calibration data.
     * @details This function configures the sensor for either 7 m/s or 15 m/s range.
     *          It loads the appropriate calibration data points for linear interpolation.
     *          The calibration data consists of raw ADC values and corresponding 
     *          velocity measurements at specific points.
     * @param range AIRFLOW_RANGE_7_MPS: PAV3000_1005 (0-7.23 m/s), 
     *              AIRFLOW_RANGE_15MPS: PAV3000_1015 (0-15 m/s)
     * @return 1: Setting successful, 0: Setting failed (I2C communication error)
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
     * @brief Get the airflow velocity in meters per second using linear interpolation.
     * @details This function implements a linear interpolation algorithm to convert
     *          raw ADC values to velocity measurements. The algorithm works as follows:
     *          1. Read raw ADC value from sensor
     *          2. Check if value is within valid range (409-3686)
     *          3. Find the calibration data points that bracket the raw value
     *          4. Calculate the percentage position within the bracket
     *          5. Apply linear interpolation: velocity = v1 + (v2-v1) * percentage
     * @return Airflow velocity in m/s, or 0.0 if sensor reading is invalid
     */
    float readMeterPerSec(void);

    /**
     * @fn readMilePerHour
     * @brief Get the airflow velocity in miles per hour (mph).
     * @return Airflow velocity data.
     */
    float readMilePerHour(void);
```

## Compatibility

MCU                | SoftwareSerial | HardwareSerial |      IIC      |
------------------ | :----------: | :----------: | :----------: | 
Arduino Uno        |      X       |      X       |      √       |
Mega2560           |      X       |      X       |      √       |
Leonardo           |      X       |      X       |      √       |
ESP32              |      X       |      X       |      √       |
ESP8266            |      X       |      X       |      √       |
micro:bit          |      X       |      X       |      √       |
FireBeetle M0      |      X       |      X       |      √       |
Raspberry Pi       |      X       |      X       |      √       |

## History

- 2024-12-02 - Version 1.0.0 released.

## Credits

Written by TangJie(jie.tang@dfrobot.com), 2025. (Welcome to our [website](https://www.dfrobot.com/))
