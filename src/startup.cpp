#include <cstdint>
#include <algorithm>

extern std::uintptr_t _rodata_begin;
extern std::uintptr_t __data_start__;
extern std::uintptr_t __data_end__;

extern std::uintptr_t __bss_start__;
extern std::uintptr_t __bss_end__;

extern void (*__ctors_begin__[])(void);
extern void (*__ctors_end__[])(void);

void init_data();
void init_bss();
void init_static_ctor();

void reset_handler()
{
    init_data();
    init_bss();
//    init_static_ctor();

    //asm volatile ("bl __libc_init_array");
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
    const std::size_t cnt = __ctors_end__ - __ctors_begin__;
    for (std::size_t i = 0; i < cnt; i++) {
        __ctors_begin__[i]();
    }
}