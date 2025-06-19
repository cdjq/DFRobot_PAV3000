# -*- coding: utf-8 -*-
"""
@file PAV3000.py
@brief This is the example code for the air velocity sensor.
@copyright Copyright (c) 2024 DFRobot Co.Ltd (http://www.dfrobot.com)
@license The MIT License (MIT)
@author [tangjie](jie.tang@dfrobot.com)
@version V1.0
@date 2024-12-03
@url https://github.com/DFRobot/DFRobot_PAV3000
"""

from __future__ import print_function
import sys
import os
sys.path.append("../")
import time

from DFRobot_PAV3000 import *

fs = DFRobot_PAV3000()

def setup():
  # Initialize PAV3000_1005
  fs.set_range(AIRFLOW_RANGE_7_MPS)
  # Comment out the above code, uncomment the below code to initialize PAV3000_1015
  #fs.set_range(AIRFLOW_RANGE_15_MPS)
  


def loop():
    print("PAV3000 Readings \tRaw: ",fs.read_raw())
    print("\tm/s: ", fs.read_meter_per_sec())
    print("\tmph: ", fs.read_mile_per_hour())
    time.sleep(1)


if __name__ == "__main__":
  setup()
  while True:
    loop()