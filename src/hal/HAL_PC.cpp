// PC-based implementation of the HAL for simulation and testing on desktop
// environments.
#include "HAL.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

class HAL_PC : public HAL {
public:
  void init() override {
    std::cout << "[HAL_PC] System Initialized" << std::endl;
  }

  void delay_ms(uint32_t ms) override {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
  }

  void log(const std::string &message) override {
    std::cout << "[LOG] " << message << std::endl;
  }

  void gpio_set_output(int pin) override {}
  void gpio_set_input(int pin) override {}

  void gpio_write(int pin, bool state) override {}

  bool gpio_read(int pin) override { return false; }

  void spi_transfer(int cs_pin, uint8_t *tx_buf, uint8_t *rx_buf,
                    size_t length) override {}

  void spi_write_reg(int cs_pin, uint8_t reg, uint8_t value) override {}

  uint8_t spi_read_reg(int cs_pin, uint8_t reg) override { return 0x00; }

  void i2c_write(int addr, uint8_t *data, size_t len) override {}

  void i2c_read(int addr, uint8_t *data, size_t len) override {}

  uint32_t analog_read(int pin_channel) override {
    return 1000 + (std::rand() % 100);
  }
};
