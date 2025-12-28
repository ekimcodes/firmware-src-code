// Defines pin mappings for SPI, I2C, and various sensors for the firmware.
#ifndef PIN_DEFINITIONS_H
#define PIN_DEFINITIONS_H

#include <stdint.h>

#define PIN_SPI_SCK 32
#define PIN_SPI_MOSI 33
#define PIN_SPI_MISO 34

#define PIN_I2C_SDA 26
#define PIN_I2C_SCL 27

#define PIN_CS_MAX30003 13
#define PIN_INT_MAX30003 14

#define PIN_CS_AD5940 15
#define PIN_INT_AD5940 16
#define PIN_RST_AD5940 17

#define PIN_CS_BMI270_L 20
#define PIN_INT_BMI270_L 21

#define PIN_AIN_EMG_L 3

#define PIN_CS_BMI270_R 22
#define PIN_INT_BMI270_R 23

#define PIN_AIN_EMG_R 4

#define PIN_BAT_MONITOR 5
#define PIN_CS_BACKUP_ECG 24

#define PIN_PWR_ENABLE 25

#endif
