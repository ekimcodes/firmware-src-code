// Implementation of the EMG AD8237 sensor driver, including mock muscle
// activation simulation.
#include "EMG_AD8237.h"
#include "../hal/HAL.h"
#include <cmath>

EMG_AD8237::EMG_AD8237(EMGChannel channel, int analogPin)
    : _channel(channel), _analogPin(analogPin), _simPhase(0.0f),
      _activationState(0.0f) {}

SensorStatus EMG_AD8237::begin() {
  SysHAL->log("[EMG] Initialized " + getName() + " on Analog Pin " +
              std::to_string(_analogPin));
  return SENSOR_OK;
}

void EMG_AD8237::update() {
  _simPhase += 0.5f;

  if (_activationState < 0.1f) {
    if ((std::rand() % 100) > 98) {
      _activationState = 1.0f;
    }
  } else {
    _activationState *= 0.95f;
  }

  float noise = ((std::rand() % 2000) - 1000);
  float signal = ((std::rand() % 10000) - 5000) * _activationState;

  _lastADC = (int32_t)(8388608 + signal + noise);
}

int32_t EMG_AD8237::getRawADC() { return _lastADC; }

float EMG_AD8237::getVoltagemV() { return (_lastADC / 16777216.0f) * 3300.0f; }

float EMG_AD8237::getActivationLevel() { return _activationState; }
