// Implementation of the MAX30003 ECG/HRV sensor driver, including mock ECG
// waveform generation.
#include "MAX30003.h"
#include "../hal/HAL.h"
#include <cmath>
#include <iostream>

#define MAX30003_REG_STATUS 0x01
#define MAX30003_REG_EN_INT 0x02
#define MAX30003_REG_ECG_CFG 0x10

MAX30003::MAX30003(int csPin, int intPin)
    : _csPin(csPin), _intPin(intPin), _mockPhase(0.0f), _mockHR(60),
      _lastRR(1.0f) {}

SensorStatus MAX30003::begin() {
  writeRegister(MAX30003_REG_ECG_CFG, 0x00);
  SysHAL->delay_ms(10);

  uint8_t id = readRegister(0x00);

  SysHAL->log("[MAX30003] Initialized on CS pin " + std::to_string(_csPin));
  return SENSOR_OK;
}

void MAX30003::update() {
  _mockPhase += 0.1f;
  if (_mockPhase > 2 * 3.14159f) {
    _mockPhase -= 2 * 3.14159f;

    _mockHR = 60 + (std::rand() % 10 - 5);
    _lastRR = 60.0f / _mockHR;
  }
}

float MAX30003::getECGVoltage() {
  float t = _mockPhase;
  float val = 0.0f;

  val += 0.1f * std::exp(-50.0f * std::pow(t - 1.0f, 2));
  val -= 0.1f * std::exp(-500.0f * std::pow(t - 2.8f, 2));
  val += 1.0f * std::exp(-1000.0f * std::pow(t - 3.0f, 2));
  val -= 0.2f * std::exp(-500.0f * std::pow(t - 3.2f, 2));
  val += 0.2f * std::exp(-30.0f * std::pow(t - 4.5f, 2));

  val += ((std::rand() % 100) / 10000.0f);

  return val;
}

int MAX30003::getHeartRate() { return _mockHR; }

float MAX30003::getRRInterval() { return _lastRR; }

void MAX30003::writeRegister(uint8_t reg, uint8_t value) {
  SysHAL->spi_write_reg(_csPin, reg, value);
}

uint8_t MAX30003::readRegister(uint8_t reg) {
  return SysHAL->spi_read_reg(_csPin, reg);
}
