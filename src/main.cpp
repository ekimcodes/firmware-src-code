// Main entry point for the firmware, initializing HAL, BLE, and sensors, and
// running the main loop.
#include <iostream>
#include <string>
#include <vector>

#include "PinDefinitions.h"
#include "communication/BLEManager.h"
#include "hal/HAL.h"

#include "drivers/AD5940.h"
#include "drivers/BMI270.h"
#include "drivers/EMG_AD8237.h"
#include "drivers/MAX30003.h"
#include "drivers/TMP117.h"

extern HAL *SysHAL;
HAL *SysHAL = nullptr;

#include "hal/HAL_PC.cpp"

HAL_PC hal_pc_instance;

MAX30003 ecgSensor(PIN_CS_MAX30003, PIN_INT_MAX30003);
AD5940 edaSensor(PIN_CS_AD5940, PIN_INT_AD5940, PIN_RST_AD5940);
TMP117 tempSensor(0x48);
BMI270 imuLeft(PIN_CS_BMI270_L, PIN_INT_BMI270_L);
BMI270 imuRight(PIN_CS_BMI270_R, PIN_INT_BMI270_R);
EMG_AD8237 emgLeft(EMG_LEFT_TRAP, PIN_AIN_EMG_L);
EMG_AD8237 emgRight(EMG_RIGHT_TRAP, PIN_AIN_EMG_R);

void setup() {
  SysHAL = &hal_pc_instance;
  SysHAL->init();

  BleStack.begin();

  SysHAL->log("--- Firmware Booting (HAL Aware) ---");

  ecgSensor.begin();
  edaSensor.begin();
  tempSensor.begin();
  imuLeft.begin();
  imuRight.begin();
  emgLeft.begin();
  emgRight.begin();

  SysHAL->log("--- Initialization Complete ---");
}

void loop() {
  ecgSensor.update();
  edaSensor.update();
  tempSensor.update();
  imuLeft.update();
  imuRight.update();
  emgLeft.update();
  emgRight.update();

  BleStack.updateHeartRate(ecgSensor.getHeartRate());
  BleStack.updateECGWaveform(ecgSensor.getECGVoltage());
  BleStack.updateEDA(edaSensor.getConductanceMicroSiemens());

  static int log_counter = 0;
  if (log_counter++ > 10) {
    log_counter = 0;
    std::string status =
        "Status: HR=" + std::to_string(ecgSensor.getHeartRate()) +
        " ECG=" + std::to_string(ecgSensor.getECGVoltage()).substr(0, 4) +
        " EDA=" +
        std::to_string(edaSensor.getConductanceMicroSiemens()).substr(0, 4) +
        " Temp=" +
        std::to_string(tempSensor.getTemperatureCelsius()).substr(0, 4);
    SysHAL->log(status);
  }

  SysHAL->delay_ms(100);
}

int main() {
  setup();
  while (true) {
    loop();
  }
  return 0;
}
