// nRF52-based implementation of the HAL for the target hardware platform.
#include "HAL.h"

class HAL_nRF : public HAL {
public:
  void init() override {}

  void delay_ms(uint32_t ms) override {}

  void log(const std::string &message) override {}

  void gpio_set_output(int pin) override {}

  void gpio_set_input(int pin) override {}

  void gpio_write(int pin, bool state) override {}

  bool gpio_read(int pin) override { return false; }

  void spi_transfer(int cs_pin, uint8_t *tx_buf, uint8_t *rx_buf,
                    size_t length) override {}

  void spi_write_reg(int cs_pin, uint8_t reg, uint8_t value) override {
    uint8_t tx[] = {reg, value};
    spi_transfer(cs_pin, tx, nullptr, 2);
  }

  uint8_t spi_read_reg(int cs_pin, uint8_t reg) override { return 0; }

  void i2c_write(int addr, uint8_t *data, size_t len) override {}

  void i2c_read(int addr, uint8_t *data, size_t len) override {}

  uint32_t analog_read(int pin_channel) override { return 0; }
};
