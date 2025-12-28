// Implementation of the AD5940 EDA sensor driver, including mock data
// generation.
#include "AD5940.h"
#include "../hal/HAL.h"
#include <cmath>
#include <iostream>

AD5940::AD5940(int csPin, int intPin, int rstPin)
    : _csPin(csPin), _intPin(intPin), _rstPin(rstPin),
      _currentConductance(0.0f), _baselineConductance(5.0f) {}

SensorStatus AD5940::begin() {
  SysHAL->delay_ms(10);

  spiWrite(0x00, 0x01);

  SysHAL->log("[AD5940] Initialized Impedance Engine on CS " +
              std::to_string(_csPin));
  return SENSOR_OK;
}

void AD5940::update() {
  _baselineConductance += 0.001f * ((std::rand() % 3) - 1);

  float phasic = 0.0f;
  if ((std::rand() % 100) > 95) {
    phasic = 1.0f + (std::rand() % 200) / 100.0f;
  }

  _currentConductance = _baselineConductance + phasic;

  if (_currentConductance < 1.0f)
    _currentConductance = 1.0f;
  if (_currentConductance > 20.0f)
    _currentConductance = 20.0f;
}

float AD5940::getConductanceMicroSiemens() { return _currentConductance; }

float AD5940::getImpedanceMagnitude() {
  if (_currentConductance > 0.0001f) {
    return (1.0f / _currentConductance) * 1000000.0f;
  }
  return 10000000.0f;
}

float AD5940::getImpedancePhase() {
  return -15.0f + ((std::rand() % 100) / 10.0f);
}

void AD5940::spiWrite(uint16_t reg, uint16_t val) {
  SysHAL->spi_write_reg(_csPin, (uint8_t)reg, (uint8_t)val);
}

uint16_t AD5940::spiRead(uint16_t reg) {
  return SysHAL->spi_read_reg(_csPin, (uint8_t)reg);
}
