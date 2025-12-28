// Header file for the TMP117 temperature sensor driver.
#ifndef TMP117_H
#define TMP117_H

#include "SensorBase.h"

class TMP117 : public SensorBase {
public:
  TMP117(int i2cAddr);

  SensorStatus begin() override;
  void update() override;
  std::string getName() const override { return "TMP117 (Temp)"; }

  float getTemperatureCelsius();

private:
  int _i2cAddr;
  float _currentTemp;
};

#endif
