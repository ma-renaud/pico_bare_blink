#ifndef RP2040_H
#define RP2040_H

#include "cmsis_rp2040.h"

#define FLASH_BASE 0x10000000UL  /*!< FLASH base address in the alias region */
#define SRAM1_BASE 0x20000000UL  /*!< SRAM1(256 KB) base address in the alias region */
#define PERIPH_BASE 0x40000000UL /*!< Peripheral base address in the alias region */

//////////////////////////////////////////////////////////////////////////

#define RESETS_BASE (PERIPH_BASE + 0xC000UL)
#define RESETS ((resets_hw_t *)RESETS_BASE) /*!< RESETS configuration struct */

typedef struct {
    __IOM uint32_t reset;
    __IOM uint32_t wdsel;
    __IOM uint32_t reset_done;
} resets_hw_t;

//////////////////////////////////////////////////////////////////////////

#define NUM_BANK0_GPIOS (30u)
#define IO_BANK0_BASE (PERIPH_BASE + 0x14000UL)
#define IO_BANK0 ((io_bank0_t *)IO_BANK0_BASE)

typedef struct {
    __IOM uint32_t status;
    __IOM uint32_t ctrl;
} io_bank0_status_ctrl_t;

typedef struct {
    __IOM uint32_t inte[4];
    __IOM uint32_t intf[4];
    __IOM uint32_t ints[4];
} io_bank0_irq_ctrl_t;

typedef struct {
    io_bank0_status_ctrl_t io[NUM_BANK0_GPIOS];

    __IOM uint32_t interrupts[4];

    io_bank0_irq_ctrl_t proc0_irq_ctrl;
    io_bank0_irq_ctrl_t proc1_irq_ctrl;
    io_bank0_irq_ctrl_t dormant_wake_irq_ctrl;
} io_bank0_t;

//////////////////////////////////////////////////////////////////////////

#define NUM_SIO_SPINLOCKS (32u)

#define SIO_BASE 0xd0000000
#define SIO ((sio_t *)SIO_BASE)

typedef struct {
    __IOM uint32_t accum0;
    __IOM uint32_t accum1;
    __IOM uint32_t base0;
    __IOM uint32_t base1;
    __IOM uint32_t base2;
    __IOM uint32_t pop_lane0;
    __IOM uint32_t pop_lane1;
    __IOM uint32_t pop_full;
    __IOM uint32_t peek_lane0;
    __IOM uint32_t peek_lane1;
    __IOM uint32_t peek_full;
    __IOM uint32_t ctrl_lane0;
    __IOM uint32_t ctrl_lane1;
    __IOM uint32_t accum0_add;
    __IOM uint32_t accum1_add;
    __IOM uint32_t base_1and0;
} sio_interpolator_t;

typedef struct {
    __IOM uint32_t cpuid;
    __IOM uint32_t gpio_in;
    __IOM uint32_t gpio_hi_in;
    __IOM uint32_t _pad0;
    __IOM uint32_t gpio_out;
    __IOM uint32_t gpio_out_set;
    __IOM uint32_t gpio_out_clr;
    __IOM uint32_t gpio_out_xor;
    __IOM uint32_t gpio_oe;
    __IOM uint32_t gpio_oe_set;
    __IOM uint32_t gpio_oe_clr;
    __IOM uint32_t gpio_oe_xor;
    __IOM uint32_t gpio_hi_out;
    __IOM uint32_t gpio_hi_out_set;
    __IOM uint32_t gpio_hi_out_clr;
    __IOM uint32_t gpio_hi_out_xor;
    __IOM uint32_t gpio_hi_oe;
    __IOM uint32_t gpio_hi_oe_set;
    __IOM uint32_t gpio_hi_oe_clr;
    __IOM uint32_t gpio_hi_oe_xor;
    __IOM uint32_t fifo_st;
    __IOM uint32_t fifo_wr;
    __IOM uint32_t fifo_rd;
    __IOM uint32_t spinlock_st;
    __IOM uint32_t div_udividend;
    __IOM uint32_t div_udivisor;
    __IOM uint32_t div_sdividend;
    __IOM uint32_t div_sdivisor;
    __IOM uint32_t div_quotient;
    __IOM uint32_t div_remainder;
    __IOM uint32_t div_csr;
    __IOM uint32_t _pad1;
    sio_interpolator_t interp0;
    sio_interpolator_t interp1;
    __IOM uint32_t spinlock[NUM_SIO_SPINLOCKS];
} sio_t;

//////////////////////////////////////////////////////////////////////////

#define CLOCKS_BASE 0x40008000
#define CLOCKS ((clocks_t *)CLOCKS_BASE)

typedef struct {
    __IOM uint32_t clk_gpout0_ctrl;
    __IOM uint32_t clk_gpout0_div;
    __IOM uint32_t clk_gpout0_selected;
    __IOM uint32_t clk_gpout1_ctrl;
    __IOM uint32_t clk_gpout1_div;
    __IOM uint32_t clk_gpout1_selected;
    __IOM uint32_t clk_gpout2_ctrl;
    __IOM uint32_t clk_gpout2_div;
    __IOM uint32_t clk_gpout2_selected;
    __IOM uint32_t clk_gpout3_ctrl;
    __IOM uint32_t clk_gpout3_div;
    __IOM uint32_t clk_gpout3_selected;
    __IOM uint32_t clk_ref_ctrl;
    __IOM uint32_t clk_ref_div;
    __IOM uint32_t clk_ref_selected;
    __IOM uint32_t clk_sys_ctrl;
    __IOM uint32_t clk_sys_div;
    __IOM uint32_t clk_sys_selected;
    __IOM uint32_t clk_peri_ctrl;
    __IOM uint32_t _pad0;
    __IOM uint32_t clk_peri_selected;
    __IOM uint32_t clk_usb_ctrl;
    __IOM uint32_t clk_usb_div;
    __IOM uint32_t clk_usb_selected;
    __IOM uint32_t clk_adc_ctrl;
    __IOM uint32_t clk_adc_div;
    __IOM uint32_t clk_adc_selected;
    __IOM uint32_t clk_rtc_ctrl;
    __IOM uint32_t clk_rtc_div;
    __IOM uint32_t clk_rtc_selected;
    __IOM uint32_t clk_sys_resus_ctrl;
    __IOM uint32_t clk_sys_resus_status;
    __IOM uint32_t fc0_ref_khz;
    __IOM uint32_t fc0_min_khz;
    __IOM uint32_t fc0_max_khz;
    __IOM uint32_t fc0_delay;
    __IOM uint32_t fc0_interval;
    __IOM uint32_t fc0_src;
    __IOM uint32_t fc0_status;
    __IOM uint32_t fc0_result;
    __IOM uint32_t wake_en0;
    __IOM uint32_t wake_en1;
    __IOM uint32_t sleep_en0;
    __IOM uint32_t sleep_en1;
    __IOM uint32_t enabled0;
    __IOM uint32_t enabled1;
    __IOM uint32_t intr;
    __IOM uint32_t inte;
    __IOM uint32_t intf;
    __IOM uint32_t ints;
} clocks_t;

//////////////////////////////////////////////////////////////////////////

#define XOSC_BASE 0x40024000
#define XOSC ((xosc_t *)XOSC_BASE)

typedef struct {
    __IOM uint32_t ctrl;
    __IOM uint32_t status;
    __IOM uint32_t dormant;
    __IOM uint32_t startup;
    __IOM uint32_t _pad0[3];
    __IOM uint32_t count;
} xosc_t;

//////////////////////////////////////////////////////////////////////////

#define PLL_SYS_BASE 0x40028000
#define PLL_SYS ((pll_t *)PLL_SYS_BASE)

#define PLL_USB_BASE 0x4002c000
#define PLL_USB ((PLL_TypeDef *)PLL_USB_BASE)

typedef struct {
    __IOM uint32_t cs;
    __IOM uint32_t pwr;
    __IOM uint32_t fbdiv_int;
    __IOM uint32_t prim;
} pll_t;

//////////////////////////////////////////////////////////////////////////

#define NUM_PWM_SLICES (8u)

#define PWM_BASE 0x40050000
#define PWM ((pwm_t *)PWM_BASE)

typedef struct pwm_slice_hw {
    __IOM uint32_t csr;
    __IOM uint32_t div;
    __IOM uint32_t ctr;
    __IOM uint32_t cc;
    __IOM uint32_t top;
} pwm_slice_t;

typedef struct {
    pwm_slice_t slice[NUM_PWM_SLICES];
    __IOM uint32_t EN;   // off 0x00a0
    __IOM uint32_t INTR; // off 0x00a4
    __IOM uint32_t INTE; // off 0x00a8
    __IOM uint32_t INTF; // off 0x00ac
    __IOM uint32_t INTS; // off 0x00b0
} pwm_t;

#endif // RP2040_H
