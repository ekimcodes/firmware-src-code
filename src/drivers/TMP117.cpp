// Implementation of the TMP117 temperature sensor driver, including mock
// temperature simulation.
#include "TMP117.h"
#include "../hal/HAL.h"
#include <cstdlib>
#include <iostream>

TMP117::TMP117(int i2cAddr) : _i2cAddr(i2cAddr), _currentTemp(36.5f) {}

SensorStatus TMP117::begin() {
  SysHAL->log("[TMP117] Initialized at I2C Addr 0x" + std::to_string(_i2cAddr));
  return SENSOR_OK;
}

void TMP117::update() {
  float noise = ((std::rand() % 100) - 50) / 500.0f;

  if (_currentTemp < 36.5f)
    _currentTemp += 0.01f;
  if (_currentTemp > 37.5f)
    _currentTemp -= 0.01f;

  _currentTemp += noise;
}

float TMP117::getTemperatureCelsius() { return _currentTemp; }
