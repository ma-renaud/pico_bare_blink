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

#define CLOCKS_BASE                        0x40008000
#define CLOCKS                             ((CLOCKS_TypeDef *) CLOCKS_BASE)

typedef struct
{
  __IO uint32_t clk_gpout0_ctrl;
  __IO uint32_t clk_gpout0_div;
  __IO uint32_t clk_gpout0_selected;
  __IO uint32_t clk_gpout1_ctrl;
  __IO uint32_t clk_gpout1_div;
  __IO uint32_t clk_gpout1_selected;
  __IO uint32_t clk_gpout2_ctrl;
  __IO uint32_t clk_gpout2_div;
  __IO uint32_t clk_gpout2_selected;
  __IO uint32_t clk_gpout3_ctrl;
  __IO uint32_t clk_gpout3_div;
  __IO uint32_t clk_gpout3_selected;
  __IO uint32_t clk_ref_ctrl;
  __IO uint32_t clk_ref_div;
  __IO uint32_t clk_ref_selected;
  __IO uint32_t clk_sys_ctrl;
  __IO uint32_t clk_sys_div;
  __IO uint32_t clk_sys_selected;
  __IO uint32_t clk_peri_ctrl;
  __IO uint32_t _pad0;
  __IO uint32_t clk_peri_selected;
  __IO uint32_t clk_usb_ctrl;
  __IO uint32_t clk_usb_div;
  __IO uint32_t clk_usb_selected;
  __IO uint32_t clk_adc_ctrl;
  __IO uint32_t clk_adc_div;
  __IO uint32_t clk_adc_selected;
  __IO uint32_t clk_rtc_ctrl;
  __IO uint32_t clk_rtc_div;
  __IO uint32_t clk_rtc_selected;
  __IO uint32_t clk_sys_resus_ctrl;
  __IO uint32_t clk_sys_resus_status;
  __IO uint32_t fc0_ref_khz;
  __IO uint32_t fc0_min_khz;
  __IO uint32_t fc0_max_khz;
  __IO uint32_t fc0_delay;
  __IO uint32_t fc0_interval;
  __IO uint32_t fc0_src;
  __IO uint32_t fc0_status;
  __IO uint32_t fc0_result;
  __IO uint32_t wake_en0;
  __IO uint32_t wake_en1;
  __IO uint32_t sleep_en0;
  __IO uint32_t sleep_en1;
  __IO uint32_t enabled0;
  __IO uint32_t enabled1;
  __IO uint32_t intr;
  __IO uint32_t inte;
  __IO uint32_t intf;
  __IO uint32_t ints;
} CLOCKS_TypeDef;


#define XOSC_BASE 0x40024000
#define XOSC ((XOSC_TypeDef *) XOSC_BASE)

typedef struct
{
    __IO uint32_t ctrl;
    __IO uint32_t status;
    __IO uint32_t dormant;
    __IO uint32_t startup;
    __IO uint32_t _pad0[3];
    __IO uint32_t count;
} XOSC_TypeDef;


#define PLL_SYS_BASE 0x40028000
#define PLL_SYS ((PLL_TypeDef *) PLL_SYS_BASE)

#define PLL_USB_BASE 0x4002c000
#define PLL_USB ((PLL_TypeDef *) PLL_USB_BASE)

typedef struct
{
    __IO uint32_t cs;
    __IO uint32_t pwr;
    __IO uint32_t fbdiv_int;
    __IO uint32_t prim;
} PLL_TypeDef;

#endif //RP2040_H
