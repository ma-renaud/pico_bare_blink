#include "clocks.h"
#include "rp2040.h"
#include "reset.h"

#define GPIO_FUNC_SIO 5u
#define LED 25u

void delay(int n) // no particular timing
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 8800; j++) {
            asm volatile("nop");
        }
    }
}

namespace {
Clock clock;
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

    [[maybe_unused]] uint32_t sys_freq = clock.get_sys_freq();
    Clock::output_clock_gpio0(Clock::gpout_src::clk_sys);

    clock.set_sys_freq(133);

    sys_freq = clock.get_sys_freq();

    // Configure led
    IO_BANK0->gpio25_ctrl = GPIO_FUNC_SIO; // init pin - select function SIO
    SIO->gpio_oe_set = 1ul << LED;         // allow setting of output
}

void loop() {
    while (true) {
        SIO->gpio_out_xor = (1ul << LED); // Toggle gpio atomically
        delay(1000);
        // SIO->gpio_out_clr = (1ul << LED); // turn off gpio atomically
        // delay(1000);
    }
}
