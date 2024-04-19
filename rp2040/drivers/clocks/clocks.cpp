#include "clocks.h"
#include "reset.h"
#include "rp2040.h"
#include "utils.h"

// Clocks
static constexpr uint8_t sys_freq_default = 6;
static constexpr uint8_t clk_peri_ctrl_enable_lsb = 11;
enum class clock_ref : uint8_t {
    rosc = 0,
    aux,
    xosc,
};
enum class clock_src : uint8_t {
    ref = 0,
    aux,
};

// XOSC
static constexpr uint8_t xosc_ctrl_enable_lsb = 12;
static constexpr uint8_t xosc_status_stable_lsb = 31;
static constexpr uint32_t xosc_status_stable_bit = 1u << xosc_status_stable_lsb;
static constexpr uint8_t xosc_status_enabled_lsb = 12;
static constexpr uint32_t xosc_status_enabled_bit = 1u << xosc_status_enabled_lsb;
static constexpr uint16_t xosc_freq_range_1_15_mhz = 0xaa0u;
static constexpr uint32_t xosc_freq = 12000000;
static constexpr uint16_t startup_delay = ((xosc_freq / 1000) + 128) / 256;

enum class xosc_status : uint16_t {
    disable = 0xd1eu,
    enable = 0xfabu,
};

// PLL
static constexpr uint8_t pll_prim_postdiv1_lsb = 16;
static constexpr uint8_t pll_prim_postdiv2_lsb = 12;
static constexpr uint8_t pll_cs_lock_lsb = 31;
static constexpr uint32_t pll_cs_lock_bit = 1u << pll_cs_lock_lsb;
static constexpr uint8_t pll_pwr_pd_lsb = 0;
static constexpr uint8_t pll_pwr_vcopd_lsb = 5;
static constexpr uint8_t pll_pwr_postdivpd_lsb = 3;
static constexpr uint32_t pll_pwr_pll_vco_start = (1u << pll_pwr_pd_lsb) | (1u << pll_pwr_vcopd_lsb);
static constexpr uint32_t pll_pwr_pllpostdiv_start = (1u << pll_pwr_postdivpd_lsb);
static constexpr uint8_t pll_post_div_1 = 6;
static constexpr uint8_t pll_post_div_2 = 2;
static constexpr uint32_t pll_post_div_config = static_cast<uint32_t>(pll_post_div_1 << pll_prim_postdiv1_lsb) |
                                                static_cast<uint32_t>(pll_post_div_2 << pll_prim_postdiv2_lsb);

// FCO
static constexpr uint8_t clk_fco_interval = 10;
static constexpr uint32_t clk_fco_max_khz = 0xffffffff;
static constexpr uint8_t clk_fco_status_running_lsb = 8;
static constexpr uint32_t clk_fco_status_running_bit = 1u << clk_fco_status_running_lsb;
static constexpr uint8_t clk_fco_status_done_lsb = 4;
static constexpr uint32_t clk_fco_status_done_bit = 1u << clk_fco_status_done_lsb;
static constexpr uint8_t clk_fco_result_khz_lsb = 5;

// GPIO0
static constexpr uint8_t gpio_21_function_clock_out = 8;
static constexpr uint8_t clk_gpio0_ctrl_src_lsb = 5;
static constexpr uint8_t clk_gpio0_ctrl_enable_lsb = 11;
static constexpr uint8_t clk_gpio0_div_lsb = 8;
static constexpr uint8_t clk_gpio0_io = 21;

clocks::clocks() : clk_sys_freq(sys_freq_default * to_underlying(hertz_units::MHZ)) {}

[[maybe_unused]] void clocks::set_sys_freq(uint32_t sys_freq_mhz) {
    if((XOSC->status & xosc_status_enabled_bit) == 0u) {
        start_xosc();
    }

    conf_pll_clock(sys_freq_mhz);
    clk_sys_freq = sys_freq_mhz * to_underlying(hertz_units::MHZ);
}

[[maybe_unused]] uint32_t clocks::frequency_count_khz(clocks::freq_counter_src src) {
    while ((CLOCKS->fc0_status & clk_fco_status_running_bit) != 0u) {}

    CLOCKS->fc0_ref_khz = xosc_freq / to_underlying(hertz_units::KHZ);
    CLOCKS->fc0_interval = clk_fco_interval;
    CLOCKS->fc0_min_khz = 0;
    CLOCKS->fc0_max_khz = clk_fco_max_khz;
    CLOCKS->fc0_src = to_underlying(src);

    while ((CLOCKS->fc0_status & clk_fco_status_done_bit) == 0u) {}

    return CLOCKS->fc0_result >> clk_fco_result_khz_lsb;
}

[[maybe_unused]] void clocks::output_clock_gpio0(clocks::gpout_src src) {    CLOCKS->clk_gpout0_ctrl =
        static_cast<uint32_t>(to_underlying(src) << clk_gpio0_ctrl_src_lsb) | 1u << clk_gpio0_ctrl_enable_lsb;
    CLOCKS->clk_gpout0_div = 1u << clk_gpio0_div_lsb;
    IO_BANK0->io[clk_gpio0_io].ctrl = gpio_21_function_clock_out;
}

[[maybe_unused]] void clocks::reset() {
    CLOCKS->clk_gpout0_ctrl = 0u;
    CLOCKS->clk_sys_ctrl = 0;
    while (CLOCKS->clk_sys_selected != 0x1) {}
    CLOCKS->clk_ref_ctrl = 0;
    while (CLOCKS->clk_ref_selected != 0x1) {}
    XOSC->ctrl = to_underlying(xosc_status::disable) << xosc_ctrl_enable_lsb;
    CLOCKS->clk_peri_ctrl |= 1u << clk_peri_ctrl_enable_lsb;
}

void clocks::start_xosc() {
    XOSC->ctrl = xosc_freq_range_1_15_mhz;
    XOSC->startup = startup_delay;
    XOSC->ctrl = to_underlying(xosc_status::enable) << xosc_ctrl_enable_lsb;

    // Wait for XOSC to be stable
    while ((XOSC->status & xosc_status_stable_bit) == 0u) {}
}

void clocks::conf_pll_clock(uint8_t sys_clock_mhz) {
    // Set Ref clock
    CLOCKS->clk_ref_ctrl = to_underlying(clock_ref::xosc);
    while ((CLOCKS->clk_ref_selected & (1u << to_underlying(clock_ref::xosc))) == 0u) {}

    // Set divider and clear PD + VCOPD
    PLL_SYS->fbdiv_int = sys_clock_mhz;
    PLL_SYS->pwr &= ~(pll_pwr_pll_vco_start);

    // Wait for PLL to lock
    while ((PLL_SYS->cs & pll_cs_lock_bit) == 0u) {}

    // Set post dividers and turn them on
    PLL_SYS->prim = pll_post_div_config;
    PLL_SYS->pwr &= ~(pll_pwr_pllpostdiv_start);

    // Set sys clock to PLL
    CLOCKS->clk_sys_ctrl = to_underlying(clock_src::aux);
    while ((CLOCKS->clk_sys_selected & (1u << to_underlying(clock_src::aux))) == 0u) {}

    // Set peripheral clock = system clock
    CLOCKS->clk_peri_ctrl |= 1u << clk_peri_ctrl_enable_lsb;
}
