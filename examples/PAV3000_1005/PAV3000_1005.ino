/*!
 * @file PAV3000_1005.ino
 * @brief This is the example code for the PAV3000_1005 air velocity sensor.
 * @copyright Copyright (c) 2024 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [tangjie](jie.tang@dfrobot.com)
 * @version V1.0
 * @date 2024-12-2
 * @url https://github.com/DFRobot/DFRobot_PAV3000
 */

#include "DFRobot_PAV3000.h"

DFRobot_PAV3000 fs;

void setup()
{
    Serial.begin(115200);

    while(!fs.setRange(AIRFLOW_RANGE_7_MPS)){
        Serial.println("Device init error");
        delay(100);
    }
    Serial.println("Device init success");

}


void loop()
{
    Serial.print("PAV3000 Readings \tRaw: ");
    Serial.print(fs.readRaw()); 
    
    Serial.print("\tm/s: ");
    Serial.print(fs.readMeterPerSec()); 
    
    Serial.print("\tmph: ");
    Serial.println(fs.readMilePerHour()); 
    
    
    delay(1000); 

}

