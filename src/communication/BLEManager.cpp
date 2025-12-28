// Implementation of the BLEManager class, handling BLE stack initialization and
// data updates.
#include "BLEManager.h"
#include "../hal/HAL.h"
#include <iomanip>
#include <iostream>

BLEManager BleStack;

void BLEManager::begin() {
  SysHAL->log("[BLE] Stack Initialized. Advertising...");
  SysHAL->log("[BLE] Connected to central.");
}

void BLEManager::updateLegacy() {}

void BLEManager::updateHeartRate(int hr) {}

void BLEManager::updateECGWaveform(float voltageMV) {}

void BLEManager::updateEDA(float conductanceUS) {}

void BLEManager::updateTemp(float tempC) {}

void BLEManager::updateEMG(float leftActivation, float rightActivation) {}

void BLEManager::updateIMU(float accZ) {}
