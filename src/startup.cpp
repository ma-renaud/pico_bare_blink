#include <cstdint>
#include <algorithm>
#include "reset.h"

//NOLINTBEGIN(bugprone-reserved-identifier, cert-dcl*, readability-identifier-naming)
extern std::uintptr_t _rodata_begin;
extern std::uintptr_t __data_start__;
extern std::uintptr_t __data_end__;

extern std::uintptr_t __bss_start__;
extern std::uintptr_t __bss_end__;

extern void (*__ctors_begin__[])(void);
extern void (*__ctors_end__[])(void);
//NOLINTEND(bugprone-reserved-identifier, cert-dcl*, readability-identifier-naming)

void init_data();
void init_bss();
void init_static_ctor();

void reset_handler()
{
    init_data();
    init_bss();

    reset::reset(reset::Peripherals::clocks);
    reset::reset(reset::Peripherals::pll_sys);

    init_static_ctor();

    asm volatile ("bl  main");
}

void init_data() {
    const std::size_t cnt = (&__data_end__ - &__data_start__);
    std::copy(&_rodata_begin, &_rodata_begin + cnt, &__data_start__);
}

void init_bss() {
    std::fill(&__bss_start__, &__bss_end__, 0U);
}

void init_static_ctor() {
    //NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    const std::size_t cnt = __ctors_end__ - __ctors_begin__;
    for (std::size_t i = 0; i < cnt; i++) {
        __ctors_begin__[i]();
    }
}