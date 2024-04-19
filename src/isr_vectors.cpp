#include <array>
#include "isr_vectors.h"
#include "core_cm0plus.h"

#define HANDLERS_OFFSET 16


extern "C" void __StackTop(void);

void reset_handler();

/**
 * Handler that won't exit. If an exception occurs, and you didn't define an handler for it, yer dead.
 */
extern "C"
{
__attribute__((noreturn)) void Unassigned_Handler(void) {
    for (;;) {
        // If you get here, An interrupt is generated and the ISR vector is not set.
        // To get which ISR number is trigged, in gdb console type this: p getVectNumber()
        // This will tell the number of the ISR called. If the ISR number is 15, mostly the systick_handler is not defined.
        // To use the systick, replace WEAK_FUNC(SysTick_Handler) by void SysTick_Handler();
        // Add the STMicro::STMicroNow library and recompile the code.
        // If the ISR number is not 15, look at array void (*isr_vector[])(void) to get the ISR name. Use the number to find the index
        asm("BKPT #0");
    }
}
}

int getVectNumber() {
    return SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk;
}

//#define ISR_LOW_MEMORY 1
#ifdef ISR_LOW_MEMORY
#warning "Modify this line to adapt it to the design. Adjust the number of element in the array"
//The number of element in the array must match. The -1 is important here. This tell that the IRQn is available
std::array<std::pair<int, std::function<void()>>,1> isrHandlers = {
    std::make_pair(-1, Unassigned_Handler)
};
void ISR()
{
    for(decltype(isrHandlers.size()) i = 0 ; i < isrHandlers.size(); ++i)
    {
        if(isrHandlers[i].first == getVectNumber())
        {
            isrHandlers[i].second();
            return;
        }
    }
}
void registerHandler(IRQn_Type irqn, std::function<void()> &&f)
{
    auto it = std::find_if(std::begin(isrHandlers), std::end(isrHandlers),
        [&irqn](auto p)
        {
            return p.first == irqn;
        }
    );

    if(it == std::end(isrHandlers))
    {
        for(decltype(isrHandlers.size()) i = 0; i < isrHandlers.size(); i++)
        {
            if(isrHandlers[i].first == -1)
            {
                isrHandlers[i] = std::make_pair(irqn, f);
            }
        }
    }
}
#else
std::array<std::function<void()>, 32> isrHandlers = {
        Unassigned_Handler, /*TIMER0_IRQHandler*/
        Unassigned_Handler, /*TIMER1_IRQHandler*/
        Unassigned_Handler, /*TIMER2_IRQHandler*/
        Unassigned_Handler, /*TIMER3_IRQHandler*/
        Unassigned_Handler, /*PWM_WRAP_IRQHandler*/
        Unassigned_Handler, /*USBCTRL_IRQHandler*/
        Unassigned_Handler, /*XIP_IRQHandler*/
        Unassigned_Handler, /*PIO0_0_IRQHandler*/
        Unassigned_Handler, /*PIO0_1_IRQHandler*/
        Unassigned_Handler, /*PIO1_0_IRQHandler*/
        Unassigned_Handler, /*PIO1_1_IRQHandler*/
        Unassigned_Handler, /*DMA0_IRQHandler*/
        Unassigned_Handler, /*DMA1_IRQHandler*/
        Unassigned_Handler, /*IO_BANK0_IRQHandler*/
        Unassigned_Handler, /*IO_QSPI_IRQHandler*/
        Unassigned_Handler, /*SIO_PROC0_IRQHandler*/
        Unassigned_Handler, /*SIO_PROC1_IRQHandler*/
        Unassigned_Handler, /*CLOCKS_IRQHandler*/
        Unassigned_Handler, /*SPI0_IRQHandler*/
        Unassigned_Handler, /*SPI1_IRQHandler*/
        Unassigned_Handler, /*UART0_IRQHandler*/
        Unassigned_Handler, /*UART1_IRQHandler*/
        Unassigned_Handler, /*ADC_FIFO_IRQHandler*/
        Unassigned_Handler, /*I2C0_IRQHandler*/
        Unassigned_Handler, /*I2C1_IRQHandler*/
        Unassigned_Handler, /*RTC_IRQHandler*/
        Unassigned_Handler, /*0*/
        Unassigned_Handler, /*0*/
        Unassigned_Handler, /*0*/
        Unassigned_Handler, /*0*/
        Unassigned_Handler, /*0*/
        Unassigned_Handler, /*0*/

};

void ISR() {
    isrHandlers[getVectNumber() - HANDLERS_OFFSET]();
}

void registerHandler(IRQn_Type irqn, std::function<void()> &&f) {
    isrHandlers[irqn] = f;
}

#endif

#define WEAK_FUNC(name) extern void name (void) __attribute__ ((weak, noreturn, nothrow, alias ("Unassigned_Handler")));

WEAK_FUNC(nmi_handler)

WEAK_FUNC(hardFault_handler)

WEAK_FUNC(svc_handler)

WEAK_FUNC(pendsv_handler)

WEAK_FUNC(systick_handler)

/*
 * ISR vectors.
 */
void (*isr_vector[])(void) __attribute__ ((used, section (".vectors"))) = {

        __StackTop, /* not a funtion */
        reset_handler,                                  // 0x0004
        nmi_handler,                                    // 0x0008
        hardFault_handler,                              // 0x000C
        0,  /* all reserved */                          // 0x0010
        0,                                              // 0x0014
        0,                                              // 0x0018
        0,                                              // 0x001C
        0,                                              // 0x0020
        0,                                              // 0x0024
        0,                                              // 0x0028
        svc_handler,                                    // 0x002C
        0,  /* reserved */                              // 0x0030
        0,                                              // 0x0034
        pendsv_handler,                                 // 0x0038
        systick_handler,                                // 0x003C
        /* RP2040 handlers */
        ISR, /*TIMER0_IRQHandler*/                      // 0x0040
        ISR, /*TIMER1_IRQHandler*/                      // 0x0044
        ISR, /*TIMER2_IRQHandler*/                      // 0x0048
        ISR, /*TIMER3_IRQHandler*/                      // 0x004C
        ISR, /*PWM_WRAP_IRQHandler*/                    // 0x0050
        ISR, /*USBCTRL_IRQHandler*/                     // 0x0054
        ISR, /*XIP_IRQHandler*/                         // 0x0058
        ISR, /*PIO0_0_IRQHandler*/                      // 0x005C
        ISR, /*PIO0_1_IRQHandler*/                      // 0x0060
        ISR, /*PIO1_0_IRQHandler*/                      // 0x0064
        ISR, /*PIO1_1_IRQHandler*/                      // 0x0068
        ISR, /*DMA0_IRQHandler*/                        // 0x006C
        ISR, /*DMA1_IRQHandler*/                        // 0x0070
        ISR, /*IO_BANK0_IRQHandler*/                    // 0x0074
        ISR, /*IO_QSPI_IRQHandler*/                     // 0x0078
        ISR, /*SIO_PROC0_IRQHandler*/                   // 0x007C
        ISR, /*SIO_PROC1_IRQHandler*/                   // 0x0080
        ISR, /*CLOCKS_IRQHandler*/                      // 0x0084
        ISR, /*SPI0_IRQHandler*/                        // 0x0088
        ISR, /*SPI1_IRQHandler*/                        // 0x008C
        ISR, /*UART0_IRQHandler*/                       // 0x0090
        ISR, /*UART1_IRQHandler*/                       // 0x0094
        ISR, /*ADC_FIFO_IRQHandler*/                    // 0x0098
        ISR, /*I2C0_IRQHandler*/                        // 0x009C
        ISR, /*I2C1_IRQHandler*/                        // 0x00A0
        ISR, /*RTC_IRQHandler*/                         // 0x00A4
        ISR, /*0*/                                      // 0x00A8
        ISR, /*0*/                                      // 0x00AC
        ISR, /*0*/                                      // 0x00B0
        ISR, /*0*/                                      // 0x00B4
        ISR, /*0*/                                      // 0x00B8
        ISR, /*0*/                                      // 0x00BC
};