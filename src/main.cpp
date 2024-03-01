#include "reset.h"
#include "rp2040.h"

#define GPIO_FUNC_SIO 5u
#define GPIO_FUNC_CLOCK_GPOUT0 8u
#define LED 25u

#define CLK_ENABLE_BIT 11u
#define CLK_SRC_LSB 5u
#define CLK_SYS_SRC 6u
#define CLK_DIV_LSB (8u)

void delay(int n) // no particular timing
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 400; j++) {
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
    reset(Peripherals::io_bank0);

    // Configure led
    IO_BANK0->gpio25_ctrl = GPIO_FUNC_SIO; // init pin - select function SIO
    SIO->gpio_oe_set = 1ul << LED;         // allow setting of output

    // Configure clock out
    CLOCKS->CLK_GPOUT0_CTRL = (CLK_SYS_SRC << CLK_SRC_LSB | 1 << CLK_ENABLE_BIT);
    CLOCKS->CLK_GPOUT0_DIV = 1 << CLK_DIV_LSB;
    IO_BANK0->gpio21_ctrl = GPIO_FUNC_CLOCK_GPOUT0; // init pin - select function SIO


    // Configure clock
    //set_sys_clock_pll(vco, postdiv1, postdiv2);
    //set_sys_clock_pll(1596000000, 6, 2);
}

void loop() {
    while (true) {
        SIO->gpio_out_xor = (1ul << LED); // Toggle gpio atomically
        delay(1000);
        // SIO->gpio_out_clr = (1ul << LED); // turn off gpio atomically
        // delay(1000);
    }
}
