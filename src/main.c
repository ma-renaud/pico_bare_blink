#define GPIO_FUNC_SIO	5
#define LED 25

#include "rp2040.h"

void unreset_block_wait(uint32_t bits) {
    RESETS->reset &= ~bits;
    while (!(RESETS->reset_done & bits)) {}
}

void delay(int n) // no particular timing
{
    for(int i =0 ; i< n; i++) {
        for(int j = 0; j< 1000; j++) {
            asm volatile ("nop");
        }
    }
}

int main() {
    unreset_block_wait(0x00000020);

    IO_BANK0->gpio25_ctrl = GPIO_FUNC_SIO; // init pin - select function SIO
    SIO->gpio_oe_set = 1ul << LED; // allow setting of output

    while(1) {
        SIO->gpio_out_xor = (1ul << LED); // Toggle gpio atomically
        delay(1000);
    }

    return 0;
}
