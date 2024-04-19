#ifndef CLOCKS_H
#define CLOCKS_H

#include "i_clocks.h"
#include <cstdint>

// See:
// https://stackoverflow.com/questions/13047526/difference-between-clocks-implemention-using-pointer-and-using-static-object

// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
class clocks : public i_clocks {
public:
    clocks(const clocks&) = delete;
    clocks(clocks&&) = delete;
    clocks& operator=(const clocks&) = delete;
    clocks& operator=(clocks&&) = delete;

    /// @brief Return the current system clock frequency
    /// @details If the clock reference is the ring oscillator the value is the imprecise because it's unstable
    uint32_t get_sys_freq() const override{
        return clk_sys_freq;
    }

    /// @brief Return the current clock reference
    clock_ref_src get_clock_reference() const override {
        return clk_ref;
    }

    /// @brief Return the current system clock frequency
    /// @details It will enable the external oscillator
    [[maybe_unused]] void set_sys_freq(uint32_t sys_freq_mhz) override;

    static i_clocks* get_instance()
    {
        static clocks instance; //NOLINT(bugprone-dynamic-static-initializers)
        return &instance;
    }

    [[maybe_unused]] static uint32_t frequency_count_khz(freq_counter_src src);
    [[maybe_unused]] static void output_clock_gpio0(gpout_src src);
    [[maybe_unused]] static void reset();

private:
    explicit clocks();
    ~clocks() = default;

    uint32_t clk_sys_freq;
    clock_ref_src clk_ref{clock_ref_src::rosc};
    static void start_xosc();
    static void conf_pll_clock(uint8_t sys_clock_mhz);
};

#endif // CLOCKS_H
