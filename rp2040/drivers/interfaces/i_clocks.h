#ifndef I_CLOCKS_H
#define I_CLOCKS_H

#include <cstdint>

class i_clocks {
public:
    enum class hertz_units : uint32_t { MHZ = 1000000, KHZ = 1000 };

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

    enum class clock_ref_src : uint8_t {
        rosc,
        xosc
    };

    /// @brief Return the current system clock frequency
    /// @details If the clock reference is the ring oscillator the value is the imprecise because it's unstable
    virtual uint32_t get_sys_freq() const = 0;

    /// @brief Return the current clock reference
    virtual clock_ref_src get_clock_reference() const = 0;

    /// @brief Return the current system clock frequency
    /// @details It will enable the external oscillator
    virtual void set_sys_freq(uint32_t sys_freq_mhz) = 0;
};

#endif // I_CLOCKS_H
