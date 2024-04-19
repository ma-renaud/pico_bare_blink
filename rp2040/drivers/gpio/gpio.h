#ifndef GPIO_H
#define GPIO_H

#include "i_gpio.h"
#include "rp2040.h"

class gpio : public i_gpio {
public:
    gpio() = default;
    ~gpio() = default;

    gpio_pinstate read() override {
        return ((1ul << gpio_num) & SIO->gpio_in) != 0u ? gpio_pinstate::SET : gpio_pinstate::RESET;
    }
    void write(gpio_pinstate pin_state) override {
        if (pin_state == gpio_pinstate::SET) {
            SIO->gpio_out_set = (1ul << gpio_num);
        } else {
            SIO->gpio_out_clr = (1ul << gpio_num);
        }
    }
    void toggle() override {
        SIO->gpio_out_xor = (1ul << gpio_num);
    }
    void init(uint8_t gpio, gpio_mode mode) override;

private:
    uint8_t gpio_num;
};

#endif // GPIO_H
