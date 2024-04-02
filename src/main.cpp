#include "reset.h"
#include "rp2040.h"
#include "utils.h"

#define GPIO_FUNC_SIO 5u
#define GPIO_FUNC_CLOCK_GPOUT0 8u
#define LED 25u

// Clocks
#define CLK_ENABLE_BIT 11u
#define CLK_SRC_LSB (5u)
#define ClK_REF_SRC (2u)

// FC0
#define CLK_DIV_LSB (8u)
#define CLK_FC0_STATUS_RUNNING_BIT (256u)
#define CLK_FC0_STATUS_DONE_BIT (16u)
#define CLK_FC0_RESULT_LSB (5u)

// PICO_CONFIG: PICO_XOSC_STARTUP_DELAY_MULTIPLIER, Multiplier to lengthen xosc startup delay to accommodate
// slow-starting oscillators, type=int, min=1, default=1, group=hardware_xosc
#ifndef PICO_XOSC_STARTUP_DELAY_MULTIPLIER
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER (1u)
#endif

#ifndef XOSC_MHZ
#define XOSC_MHZ (12u)
#endif

// Pll
#define PLL_CS_LOCK_BITS (0x80000000u)
#define PLL_PRIM_POSTDIV1_LSB (16u)
#define PLL_PRIM_POSTDIV2_LSB (12u)

#define KHZ 1000
#define MHZ 1000000

#define XOSC_CTRL_ENABLE_VALUE_ENABLE (0xfabu)
#define XOSC_CTRL_ENABLE_LSB (12u)
#define XOSC_STATUS_STABLE_BITS (0x80000000u)
#define XOSC_CTRL_FREQ_RANGE_VALUE_1_15MHZ (0xaa0u)
#define STARTUP_DELAY (((((XOSC_MHZ * MHZ) / 1000) + 128) / 256) * PICO_XOSC_STARTUP_DELAY_MULTIPLIER)

enum class gpout_src : uint8_t {
    clk_src_pll_sys,
    clk_src_gpin0,
    clk_src_gpin1,
    clk_src_pll_usb,
    clk_src_rosc,
    clk_src_xosc,
    clk_sys,
    clk_usb,
    clk_adc,
    clk_rtc,
    clk_ref
};

enum class freq_counter_src : uint8_t {
    null,
    clk_src_pll_sys,
    clk_src_pll_usb,
    clk_src_rosc,
    clk_src_rosc_ph,
    clk_src_xosc,
    clk_src_gpin0,
    clk_src_gpin1,
    clk_ref,
    clk_sys,
    clk_peri,
    clk_usb,
    clk_adc,
    clk_rtc
};

void delay(int n) // no particular timing
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 8800; j++) {
            asm volatile("nop");
        }
    }
}

uint32_t frequency_count_khz(freq_counter_src src) {
    while ((CLOCKS->fc0_status & CLK_FC0_STATUS_RUNNING_BIT)) {}

    CLOCKS->fc0_ref_khz = 12000;
    CLOCKS->fc0_interval = 10;
    CLOCKS->fc0_min_khz = 0;
    CLOCKS->fc0_max_khz = 0xffffffff;
    CLOCKS->fc0_src = to_underlying(src);

    while (!(CLOCKS->fc0_status & CLK_FC0_STATUS_DONE_BIT)) {}

    return CLOCKS->fc0_result >> CLK_FC0_RESULT_LSB;
}

void clock_out_gpio0(gpout_src src) {
    CLOCKS->clk_gpout0_ctrl = static_cast<uint32_t>(to_underlying(src) << CLK_SRC_LSB) | 1u << CLK_ENABLE_BIT;
    CLOCKS->clk_gpout0_div = 1u << CLK_DIV_LSB;
    IO_BANK0->gpio21_ctrl = GPIO_FUNC_CLOCK_GPOUT0; // init pin - select function SIO
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

    // Configure led
    IO_BANK0->gpio25_ctrl = GPIO_FUNC_SIO; // init pin - select function SIO
    SIO->gpio_oe_set = 1ul << LED;         // allow setting of output

    // Start external oscillator
    XOSC->ctrl = XOSC_CTRL_FREQ_RANGE_VALUE_1_15MHZ;
    XOSC->startup = STARTUP_DELAY;
    XOSC->ctrl = XOSC_CTRL_ENABLE_VALUE_ENABLE << XOSC_CTRL_ENABLE_LSB;

    // Wait for XOSC to be stable
    while ((XOSC->status & XOSC_STATUS_STABLE_BITS) == 0u) {}

    // Configure clock
    // Set Ref
    CLOCKS->clk_ref_ctrl = ClK_REF_SRC;

    // Set divider and clear PD + VCOPD
    PLL_SYS->fbdiv_int = 133;
    PLL_SYS->pwr &= ~(0x21);

    // Wait for PLL to lock
    while ((PLL_SYS->cs & PLL_CS_LOCK_BITS) == 0u) {}

    // Set post dividers and turn them on
    PLL_SYS->prim = (6 << PLL_PRIM_POSTDIV1_LSB) | (2 << PLL_PRIM_POSTDIV2_LSB);
    PLL_SYS->pwr &= ~(0x8);

    // Set sys clock to PLL
    CLOCKS->clk_sys_ctrl |= 1u;

    clock_out_gpio0(gpout_src::clk_sys);

    uint32_t freq_khz = frequency_count_khz(freq_counter_src::clk_sys);
    uint32_t freq_mhz = freq_khz / 1000;
    uint32_t test = 42;

    // Configure clock
    // set_sys_clock_pll(vco, postdiv1, postdiv2);
    // set_sys_clock_pll(1596000000, 6, 2);
}

void loop() {
    while (true) {
        SIO->gpio_out_xor = (1ul << LED); // Toggle gpio atomically
        delay(1000);
        // SIO->gpio_out_clr = (1ul << LED); // turn off gpio atomically
        // delay(1000);
    }
}
