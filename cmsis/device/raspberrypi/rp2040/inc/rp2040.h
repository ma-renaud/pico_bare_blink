#ifndef RP2040_H
#define RP2040_H

#include "cmsis_rp2040.h"

#define FLASH_BASE                      0x10000000UL /*!< FLASH base address in the alias region */
#define SRAM1_BASE                      0x20000000UL /*!< SRAM1(256 KB) base address in the alias region */
#define PERIPH_BASE                     0x40000000UL /*!< Peripheral base address in the alias region */

#define RESETS_BASE                     (PERIPH_BASE + 0xC000UL)
#define RESETS                          ((resets_hw_t *) RESETS_BASE )   /*!< RESETS configuration struct */

typedef struct
{
    __IOM uint32_t reset;
    __IOM uint32_t wdsel;
    __IM  uint32_t reset_done;
} resets_hw_t;

#define IO_BANK0_BASE                   (PERIPH_BASE + 0x14000UL)
#define IO_BANK0                        ((IO_BANK0_TypeDef *) IO_BANK0_BASE)

typedef struct
{
    __IO uint32_t gpio0_status;
    __IO uint32_t gpio0_ctrl;
    __IO uint32_t gpio1_status;
    __IO uint32_t gpio1_ctrl;
    __IO uint32_t gpio2_status;
    __IO uint32_t gpio2_ctrl;
    __IO uint32_t gpio3_status;
    __IO uint32_t gpio3_ctrl;
    __IO uint32_t gpio4_status;
    __IO uint32_t gpio4_ctrl;
    __IO uint32_t gpio5_status;
    __IO uint32_t gpio5_ctrl;
    __IO uint32_t gpio6_status;
    __IO uint32_t gpio6_ctrl;
    __IO uint32_t gpio7_status;
    __IO uint32_t gpio7_ctrl;
    __IO uint32_t gpio8_status;
    __IO uint32_t gpio8_ctrl;
    __IO uint32_t gpio9_status;
    __IO uint32_t gpio9_ctrl;
    __IO uint32_t gpio10_status;
    __IO uint32_t gpio10_ctrl;
    __IO uint32_t gpio11_status;
    __IO uint32_t gpio11_ctrl;
    __IO uint32_t gpio12_status;
    __IO uint32_t gpio12_ctrl;
    __IO uint32_t gpio13_status;
    __IO uint32_t gpio13_ctrl;
    __IO uint32_t gpio14_status;
    __IO uint32_t gpio14_ctrl;
    __IO uint32_t gpio15_status;
    __IO uint32_t gpio15_ctrl;
    __IO uint32_t gpio16_status;
    __IO uint32_t gpio16_ctrl;
    __IO uint32_t gpio17_status;
    __IO uint32_t gpio17_ctrl;
    __IO uint32_t gpio18_status;
    __IO uint32_t gpio18_ctrl;
    __IO uint32_t gpio19_status;
    __IO uint32_t gpio19_ctrl;
    __IO uint32_t gpio20_status;
    __IO uint32_t gpio20_ctrl;
    __IO uint32_t gpio21_status;
    __IO uint32_t gpio21_ctrl;
    __IO uint32_t gpio22_status;
    __IO uint32_t gpio22_ctrl;
    __IO uint32_t gpio23_status;
    __IO uint32_t gpio23_ctrl;
    __IO uint32_t gpio24_status;
    __IO uint32_t gpio24_ctrl;
    __IO uint32_t gpio25_status;
    __IO uint32_t gpio25_ctrl;
    __IO uint32_t gpio26_status;
    __IO uint32_t gpio26_ctrl;
    __IO uint32_t gpio27_status;
    __IO uint32_t gpio27_ctrl;
    __IO uint32_t gpio28_status;
    __IO uint32_t gpio28_ctrl;
    __IO uint32_t gpio29_status;
    __IO uint32_t gpio29_ctrl;
    __IO uint32_t intr0;
    __IO uint32_t intr1;
    __IO uint32_t intr2;
    __IO uint32_t intr3;
    __IO uint32_t proc0_inte0;
    __IO uint32_t proc0_inte1;
    __IO uint32_t proc0_inte2;
    __IO uint32_t proc0_inte3;
    __IO uint32_t proc0_intf0;
    __IO uint32_t proc0_intf1;
    __IO uint32_t PROC0_INTF2;
    __IO uint32_t proc0_intf3;
    __IO uint32_t proc0_ints0;
    __IO uint32_t proc0_ints1;
    __IO uint32_t proc0_ints2;
    __IO uint32_t proc0_ints3;
    __IO uint32_t proc1_inte0;
    __IO uint32_t proc1_inte1;
    __IO uint32_t proc1_inte2;
    __IO uint32_t proc1_inte3;
    __IO uint32_t proc1_intf0;
    __IO uint32_t proc1_intf1;
    __IO uint32_t proc1_intf2;
    __IO uint32_t proc1_intf3;
    __IO uint32_t proc1_ints0;
    __IO uint32_t proc1_ints1;
    __IO uint32_t proc1_ints2;
    __IO uint32_t proc1_ints3;
    __IO uint32_t dormant_wake_inte0;
    __IO uint32_t dormant_wake_inte1;
    __IO uint32_t dormant_wake_inte2;
    __IO uint32_t dormant_wake_inte3;
    __IO uint32_t dormant_wake_intf0;
    __IO uint32_t dormant_wake_intf1;
    __IO uint32_t dormant_wake_intf2;
    __IO uint32_t dormant_wake_intf3;
    __IO uint32_t dormant_wake_ints0;
    __IO uint32_t dormant_wake_ints1;
    __IO uint32_t dormant_wake_ints2;
    __IO uint32_t dormant_wake_ints3;
} IO_BANK0_TypeDef;

#define SIO_BASE                        0xd0000000
#define SIO                             ((SIO_TypeDef *) SIO_BASE)

typedef struct
{
    __IO uint32_t cpuid;
    __IO uint32_t gpio_in;
    __IO uint32_t gpio_hi_in;
    __IO uint32_t _pad0;
    __IO uint32_t gpio_out;
    __IO uint32_t gpio_out_set;
    __IO uint32_t gpio_out_clr;
    __IO uint32_t gpio_out_xor;
    __IO uint32_t gpio_oe;
    __IO uint32_t gpio_oe_set;
    __IO uint32_t gpio_oe_clr;
    __IO uint32_t gpio_oe_xor;
    __IO uint32_t gpio_hi_out;
    __IO uint32_t gpio_hi_out_set;
    __IO uint32_t gpio_hi_out_clr;
    __IO uint32_t gpio_hi_out_xor;
    __IO uint32_t gpio_hi_oe;
    __IO uint32_t gpio_hi_oe_set;
    __IO uint32_t gpio_hi_oe_clr;
    __IO uint32_t gpio_hi_oe_xor;
    __IO uint32_t fifo_st;
    __IO uint32_t fifo_wr;
    __IO uint32_t fifo_rd;
    __IO uint32_t spinlock_st;
    __IO uint32_t div_udividend;
    __IO uint32_t div_udivisor;
    __IO uint32_t div_sdividend;
    __IO uint32_t div_sdivisor;
    __IO uint32_t div_quotient;
    __IO uint32_t div_remainder;
    __IO uint32_t div_csr;
    __IO uint32_t _pad1;
    __IO uint32_t interp0_accum0;
    __IO uint32_t interp0_accum1;
    __IO uint32_t interp0_base0;
    __IO uint32_t interp0_base1;
    __IO uint32_t interp0_base2;
    __IO uint32_t interp0_pop_lane0;
    __IO uint32_t interp0_pop_lane1;
    __IO uint32_t interp0_pop_full;
    __IO uint32_t interp0_peek_lane0;
    __IO uint32_t interp0_peek_lane1;
    __IO uint32_t interp0_peek_full;
    __IO uint32_t interp0_ctrl_lane0;
    __IO uint32_t interp0_ctrl_lane1;
    __IO uint32_t interp0_accum0_add;
    __IO uint32_t interp0_accum1_add;
    __IO uint32_t interp0_base_1and0;
    __IO uint32_t interp1_accum0;
    __IO uint32_t interp1_accum1;
    __IO uint32_t interp1_base0;
    __IO uint32_t interp1_base1;
    __IO uint32_t interp1_base2;
    __IO uint32_t interp1_pop_lane0;
    __IO uint32_t interp1_pop_lane1;
    __IO uint32_t interp1_pop_full;
    __IO uint32_t interp1_peek_lane0;
    __IO uint32_t interp1_peek_lane1;
    __IO uint32_t interp1_peek_full;
    __IO uint32_t interp1_ctrl_lane0;
    __IO uint32_t interp1_ctrl_lane1;
    __IO uint32_t interp1_accum0_add;
    __IO uint32_t interp1_accum1_add;
    __IO uint32_t interp1_base_1and0;
    __IO uint32_t spinlock0;
    __IO uint32_t spinlock1;
    __IO uint32_t spinlock2;
    __IO uint32_t spinlock3;
    __IO uint32_t spinlock4;
    __IO uint32_t spinlock5;
    __IO uint32_t spinlock6;
    __IO uint32_t spinlock7;
    __IO uint32_t spinlock8;
    __IO uint32_t spinlock9;
    __IO uint32_t spinlock10;
    __IO uint32_t spinlock11;
    __IO uint32_t spinlock12;
    __IO uint32_t spinlock13;
    __IO uint32_t spinlock14;
    __IO uint32_t spinlock15;
    __IO uint32_t spinlock16;
    __IO uint32_t spinlock17;
    __IO uint32_t spinlock18;
    __IO uint32_t spinlock19;
    __IO uint32_t spinlock20;
    __IO uint32_t spinlock21;
    __IO uint32_t spinlock22;
    __IO uint32_t spinlock23;
    __IO uint32_t spinlock24;
    __IO uint32_t spinlock25;
    __IO uint32_t spinlock26;
    __IO uint32_t spinlock27;
    __IO uint32_t spinlock28;
    __IO uint32_t spinlock29;
    __IO uint32_t spinlock30;
    __IO uint32_t spinlock31;
} SIO_TypeDef;

#endif //RP2040_H
