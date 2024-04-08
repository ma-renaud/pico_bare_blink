#ifndef CLOCKS_H
#define CLOCKS_H

#include <cstdint>

class Clock {
public:
    explicit Clock();
    ~Clock() = default;

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
    uint32_t get_sys_freq() const {
        return clk_sys_freq;
    }

    /// @brief Return the current clock reference
    clock_ref_src get_clock_reference() const {
        return clk_ref;
    }

    [[maybe_unused]] void set_sys_freq(uint32_t sys_freq_mhz);
    [[maybe_unused]] static uint32_t frequency_count_khz(freq_counter_src src);
    [[maybe_unused]] static void output_clock_gpio0(gpout_src src);
    [[maybe_unused]] static void reset();

private:
    uint32_t clk_sys_freq;
    clock_ref_src clk_ref {clock_ref_src::rosc};
    static void start_xosc();
    static void conf_pll_clock(uint8_t sys_clock_mhz);
};

#endif // CLOCKS_H
