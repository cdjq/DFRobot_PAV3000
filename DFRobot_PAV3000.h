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

#define AIRFLOW_RANGE_7_MPS 0x08 ///< 7 m/s range
#define AIRFLOW_RANGE_15_MPS 0x0C ///< 15 m/s range

#define PAV3000_I2C_ADDRESS          0x28 ///< device address
#define PAV3000_MIN_RAW_VALUE        409 ///< minimum raw value
#define PAV3000_MAX_RAW_VALUE        3686 ///< maximum raw value
#define PAV3000_7MPS_MAX_VELOCITY    7.23f ///< maximum velocity in m/s for 7 m/s range
#define PAV3000_15MPS_MAX_VELOCITY   15.00f ///< maximum velocity in m/s for 15 m/s range
#define PAV3000_MPH_CONVERSION_FACTOR 2.2369362912f ///< conversion factor from m/s to mph

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
    };

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


private:
    TwoWire *_pWire;

    uint8_t readData(void* buf, uint8_t len);
    bool checkSum(void* buf);
    float _mpsDataPoint[13]; 
    int _rawDataPoint[13]; 
    uint8_t _addr = PAV3000_I2C_ADDRESS;
    uint8_t _range = 0;


};

#endif
