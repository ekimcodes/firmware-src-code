// Header file for the MAX30003 ECG/HRV sensor driver.
#ifndef MAX30003_H
#define MAX30003_H

#include "SensorBase.h"

class MAX30003 : public SensorBase {
public:
  MAX30003(int csPin, int intPin);

  SensorStatus begin() override;
  void update() override;
  std::string getName() const override { return "MAX30003 (ECG/HRV)"; }

  float getECGVoltage();
  int getHeartRate();
  float getRRInterval();

private:
  int _csPin;
  int _intPin;

  float _mockPhase;
  int _mockHR;
  float _lastRR;

  void writeRegister(uint8_t reg, uint8_t value);
  uint8_t readRegister(uint8_t reg);
};

#endif
