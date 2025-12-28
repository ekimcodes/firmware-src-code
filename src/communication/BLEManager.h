// Header file for the BLEManager class, defining the interface for BLE
// operations.
#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

#include <stdint.h>
#include <string>

class BLEManager {
public:
  void begin();
  void updateLegacy();

  void updateHeartRate(int hr);
  void updateECGWaveform(float voltageMV);
  void updateEDA(float conductanceUS);
  void updateTemp(float tempC);
  void updateEMG(float leftActivation, float rightActivation);
  void updateIMU(float accZ);
};

extern BLEManager BleStack;

#endif
