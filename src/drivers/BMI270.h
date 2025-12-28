// Header file for the BMI270 IMU sensor driver.
#ifndef BMI270_H
#define BMI270_H

#include "SensorBase.h"

struct IMUData {
  float accelX, accelY, accelZ;
  float gyroX, gyroY, gyroZ;
};

class BMI270 : public SensorBase {
public:
  BMI270(int csPin, int intPin);

  SensorStatus begin() override;
  void update() override;
  std::string getName() const override { return "BMI270 (IMU)"; }

  IMUData getData();

private:
  int _csPin;
  int _intPin;

  IMUData _data;
  float _simTime;
};

#endif
