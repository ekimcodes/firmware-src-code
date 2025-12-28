// Abstract base class defining the standard interface for all sensor drivers.
#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

#include <stdint.h>
#include <string>

enum SensorStatus {
  SENSOR_OK = 0,
  SENSOR_ERROR_INIT,
  SENSOR_ERROR_READ,
  SENSOR_ERROR_TIMEOUT
};

class SensorBase {
public:
  virtual ~SensorBase() {}

  virtual SensorStatus begin() = 0;

  virtual void update() = 0;

  virtual std::string getName() const = 0;

protected:
};

#endif
