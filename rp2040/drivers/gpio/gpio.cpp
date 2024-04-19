#include "gpio.h"

static constexpr uint8_t gpio_func_sio = 5;

void gpio::init(uint8_t gpio, gpio_mode mode) {
    gpio_num = gpio;

    switch (mode) {
    case gpio_mode::GPIO:
        IO_BANK0->io[gpio_num].ctrl = gpio_func_sio;
        SIO->gpio_oe_set = 1ul << gpio_num;
        break;
    default:
        break;
    }
}
