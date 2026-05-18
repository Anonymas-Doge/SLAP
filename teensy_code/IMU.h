#ifndef IMU_H
#define IMU_H

// include connected files later
#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_BNO080_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_BNO080

void IMU_setup();
void IMU_loop();

#endif