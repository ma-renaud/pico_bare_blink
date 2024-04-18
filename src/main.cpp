#include "clocks.h"
#include "gpio.h"
#include "reset.h"

#define LED_IO 25u

namespace {
gpio led;
}

void delay(int n) // no particular timing
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 8800; j++) {
            asm volatile("nop");
        }
    }
}

void init();
[[noreturn]] void loop();

int main() {
    init();
    loop();
    return 0;
}

void init() {
    reset::reset(reset::Peripherals::bus_ctrl);
    reset::reset(reset::Peripherals::io_bank0);

    i_clocks *clock = clocks::get_instance();
    [[maybe_unused]] uint32_t sys_freq = clock->get_sys_freq();

    // Configure led
    led.init(LED_IO, gpio_mode::GPIO);
}

void loop() {
    while (true) {
        led.toggle();
        delay(1000);
    }
}
