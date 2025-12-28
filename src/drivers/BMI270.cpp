// Implementation of the BMI270 IMU sensor driver, including mock data
// generation.
#include "BMI270.h"
#include "../hal/HAL.h"
#include <cmath>

BMI270::BMI270(int csPin, int intPin)
    : _csPin(csPin), _intPin(intPin), _simTime(0.0f) {
  _data = {0, 0, 0, 0, 0, 0};
}

SensorStatus BMI270::begin() {
  SysHAL->log("[BMI270] Initialized on CS " + std::to_string(_csPin));
  return SENSOR_OK;
}

void BMI270::update() {
  _simTime += 0.05f;

  _data.accelX = 0.1f * std::sin(_simTime);
  _data.accelY = 0.2f * std::cos(_simTime * 2.0f);
  _data.accelZ = 0.98f + 0.3f * std::abs(std::sin(_simTime * 3.0f));

  _data.gyroX = 5.0f * std::sin(_simTime);
  _data.gyroY = 5.0f * std::cos(_simTime);
  _data.gyroZ = 2.0f * std::sin(_simTime * 0.5f);
}

IMUData BMI270::getData() { return _data; }
