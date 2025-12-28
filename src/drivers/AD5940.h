// Header file for the AD5940 EDA sensor driver.
#ifndef AD5940_H
#define AD5940_H

#include "SensorBase.h"

class AD5940 : public SensorBase {
public:
  AD5940(int csPin, int intPin, int rstPin);

  SensorStatus begin() override;
  void update() override;
  std::string getName() const override { return "AD5940 (EDA)"; }

  float getConductanceMicroSiemens();
  float getImpedanceMagnitude();
  float getImpedancePhase();

private:
  int _csPin;
  int _intPin;
  int _rstPin;

  float _currentConductance;
  float _baselineConductance;

  void spiWrite(uint16_t reg, uint16_t val);
  uint16_t spiRead(uint16_t reg);
};

#endif
