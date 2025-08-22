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
            @brief 设置气流检测范围并初始化校准数据。
            @details 本函数将传感器配置为 7 m/s 或 15 m/s 量程，并加载相应的校准数据点用于线性插值。
                     校准数据由原始 ADC 值及对应的特定点气流速度组成。
            @param range AIRFLOW_RANGE_7_MPS: PAV3000_1005 (0-7.23 m/s)，
                         AIRFLOW_RANGE_15MPS: PAV3000_1015 (0-15 m/s)
            @return 1: 设置成功，0: 设置失败（I2C 通信错误）
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
            @brief 使用线性插值法获取以米每秒为单位的气流速度。
            @details 本函数通过线性插值算法将原始 ADC 值转换为速度测量值。算法流程如下：
                     1. 从传感器读取原始 ADC 值
                     2. 检查数值是否在有效范围内 (409-3686)
                     3. 找到包围该原始值的校准数据点
                     4. 计算原始值在区间内的百分比位置
                     5. 应用线性插值公式：velocity = v1 + (v2 - v1) * percentage
            @return 返回气流速度（单位：m/s），若传感器读数无效则返回 0.0
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