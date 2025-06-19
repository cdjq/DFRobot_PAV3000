DFRobot_PAV3000
===========================

* [English Version](./README.md)

这是一个空气流速传感器的驱动库。

![产品效果图片](./resources/images/SEN0501.png)
![产品效果图片](./resources/images/SEN0500.png)

## 产品链接（https://www.dfrobot.com）

    SKU：NULL
  
## 目录

  * [概述](#概述)
  * [库安装](#库安装)
  * [方法](#方法)
  * [兼容性](#兼容性)
  * [历史](#历史)
  * [创作者](#创作者)

## 概述

这是一个空气流速传感器的驱动库。

## 库安装

使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法

```C++
    /**
     * @fn setRange
     * @brief 设置空气流速检测距离
     * @param range AIRFLOW_RANGE_7_MPS:PAV3000_1005 AIRFLOW_RANGE_15MPS:PAV3000_1015
     * @return 1：设置成功， 0：设置失败
     */
    uint8_t setRange(uint8_t range);

    /**
     * @fn readRaw
     * @brief 获取传感器得原始数据
     * @return PAV3000 寄存器原始数据
     */
    uint16_t readRaw(void);

    /**
     * @fn readMeterPerSec
     * @brief 获取米/秒为单位的空气流速
     * @return 空气流速数据
     */
    float readMeterPerSec(void);

    /**
     * @fn readMilePerHour
     * @brief 获取英里/小时为单位的空气流速
     * @return 空气流速数据
     */
    float readMilePerHour(void);
```


## 兼容性

MCU                | SoftwareSerial | HardwareSerial |      IIC      |
------------------ | :----------: | :----------: | :----------: | 
Arduino Uno        |      X       |      X       |      √       |
Mega2560           |      X       |      X       |      √       |
Leonardo           |      X       |      X       |      √       |
ESP32              |      X       |      X       |      √       |
ESP8266            |      X       |      X       |      √       |
micro:bit          |      X       |      X       |      √       |
FireBeetle M0      |      X       |      X       |      √       |
raspberry          |      X       |      X       |      √       |

## 历史
- 2024-12-05 - 1.0.0 版本

## 创作者

Written by TangJie(jie.tang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))