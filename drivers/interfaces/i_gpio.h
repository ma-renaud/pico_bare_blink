#ifndef I_GPIO_H
#define I_GPIO_H

#include <cstdint>

enum class gpio_pinstate : uint8_t { RESET = 0, SET };

enum class gpio_mode : uint8_t {
    GPIO = 0,
    SPI,
    UART,
    I2C,
    PWM,
    PIO,
    CLK_IN,
    CLK_OUT,
};

class i_gpio {
public:
    virtual gpio_pinstate read() = 0;
    virtual void write(gpio_pinstate pin_state) = 0;
    virtual void toggle() = 0;
    virtual void init(uint8_t gpio, gpio_mode mode) = 0;
};

#endif // I_GPIO_H
