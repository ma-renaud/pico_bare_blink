#include "reset.h"
#include "rp2040.h"
#include "utils.h"
#include "clocks.h"

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

void init();
[[noreturn]] void loop();

int main() {
    init();
    loop();
    return 0;
}

void init() {
    reset(Peripherals::bus_ctrl);
    reset(Peripherals::io_bank0);
    reset(Peripherals::pll_sys);

    uint32_t freq_khz = Clock::frequency_count_khz(Clock::freq_counter_src::clk_sys);
    uint32_t freq_mhz = freq_khz / to_underlying(Clock::hertz_units::KHZ);
    (void)freq_mhz;

    Clock::output_clock_gpio0(Clock::gpout_src::clk_sys);

    Clock clock;
    uint32_t test = clock.get_sys_freq();
    clock.set_sys_freq(84);
    test = clock.get_sys_freq();
    (void)test;

    freq_khz = Clock::frequency_count_khz(Clock::freq_counter_src::clk_sys);
    freq_mhz = freq_khz / to_underlying(Clock::hertz_units::KHZ);
    (void)freq_mhz;

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
