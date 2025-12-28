// Header file for the EMG AD8237 sensor driver.
#ifndef EMG_AD8237_H
#define EMG_AD8237_H

#include "SensorBase.h"

enum EMGChannel { EMG_LEFT_TRAP = 0, EMG_RIGHT_TRAP };

class EMG_AD8237 : public SensorBase {
public:
  EMG_AD8237(EMGChannel channel, int analogPin);

  SensorStatus begin() override;
  void update() override;
  std::string getName() const override {
    return (_channel == EMG_LEFT_TRAP) ? "EMG (Left Trap)" : "EMG (Right Trap)";
  }

  int32_t getRawADC();
  float getVoltagemV();
  float getActivationLevel();

private:
  EMGChannel _channel;
  int _analogPin;

  float _simPhase;
  float _activationState;
  int32_t _lastADC;
};

#endif
