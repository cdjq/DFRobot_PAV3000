DFRobot_PAV3000
===========================

* [English Version](./README.md)

这是一个空气流速传感器的驱动库。

![产品效果图片](../../resources/images/SEN0501.png)
![产品效果图片](../../resources/images/SEN0500.png)

## 产品链接（https://www.dfrobot.com）

    SKU：无
  
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

要使用这个库，首先将库下载到Raspberry Pi，然后打开例程文件夹。要执行一个例程demox.py，请在命令行中输入python demox.py。例如，要执行control_led.py例程，你需要输入:

```python
python PAV3000.py
```

## 方法

```python
    def set_range(self, range):
        '''
            @fn set_range
            @brief 设置空气流速检测距离
            @range AIRFLOW_RANGE_7_MPS:PAV3000_1005 AIRFLOW_RANGE_15MPS:PAV3000_1015
        '''

    def read_raw(self):
        '''
            @fn read_raw
            @brief 获取传感器得原始数据
            @return PAV3000 寄存器原始数据
        '''
    
    def read_meter_per_sec(self):
        '''
            @fn read_meter_per_sec
            @brief 获取米/秒为单位的空气流速
            @return 空气流速数据
        '''
    
    def read_mile_per_hour(self):
        '''
            @fn read_mile_per_hour
            @brief 获取英里/小时为单位的空气流速
            @return 空气流速数据
        '''
```

## 兼容性

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |     √     |            |          |         |
| RaspberryPi4 |           |            |     √    |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |

## 历史

- 2024-12-03 - 1.0.0 版本

## 创作者

Written by TangJie(jie.tang@dfrobot.com), 2025. (Welcome to our [website](https://www.dfrobot.com/))