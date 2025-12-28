// Hardware Abstraction Layer (HAL) interface definition for
// platform-independent hardware access.
#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <string>
#include <vector>

class HAL {
public:
  virtual ~HAL() {}

  virtual void init() = 0;
  virtual void delay_ms(uint32_t ms) = 0;
  virtual void log(const std::string &message) = 0;

  virtual void gpio_set_output(int pin) = 0;
  virtual void gpio_set_input(int pin) = 0;
  virtual void gpio_write(int pin, bool state) = 0;
  virtual bool gpio_read(int pin) = 0;

  virtual void spi_transfer(int cs_pin, uint8_t *tx_buf, uint8_t *rx_buf,
                            size_t length) = 0;

  virtual void spi_write_reg(int cs_pin, uint8_t reg, uint8_t value) = 0;

  virtual uint8_t spi_read_reg(int cs_pin, uint8_t reg) = 0;

  virtual void i2c_write(int addr, uint8_t *data, size_t len) = 0;
  virtual void i2c_read(int addr, uint8_t *data, size_t len) = 0;

  virtual uint32_t analog_read(int pin_channel) = 0;
};

extern HAL *SysHAL;

#endif
