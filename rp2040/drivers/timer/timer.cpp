#include "timer.h"
#include "rp2040.h"
#include "utils.h"

static constexpr uint8_t pwm_div_int_lsb = 4;
static constexpr uint8_t pwm_csr_en_lsb = 0;

timer::timer(timer::ident timer_ident) : timer_ident(timer_ident) {}

void timer::init(uint16_t period, uint8_t prescaler) {
    uint8_t timer_num = to_underlying(timer_ident);

    PWM->slice[timer_num].csr = 0;
    PWM->slice[timer_num].ctr = 0;
    PWM->slice[timer_num].cc = 0;
    PWM->slice[timer_num].top = period;
    PWM->slice[timer_num].div = prescaler << pwm_div_int_lsb;
}

void timer::start() {
    PWM->slice[to_underlying(timer_ident)].csr |= 1u << pwm_csr_en_lsb;
}

void timer::start_one_time() {
    one_time_mode = true;
    start();
}

void timer::stop() {
    PWM->slice[to_underlying(timer_ident)].csr &= ~(1u << pwm_csr_en_lsb);
}

void timer::register_callback(std::function<void()> &&function) {
    callback = std::move(function);
}

void timer::enable_interrupts(uint32_t priority) {
    NVIC_SetPriority(PWM_IRQ_WRAP_IRQn, priority);
    __NVIC_ClearPendingIRQ(PWM_IRQ_WRAP_IRQn);
    __NVIC_EnableIRQ(PWM_IRQ_WRAP_IRQn);
    PWM->INTE |= 1u << to_underlying(timer_ident);
}

void timer::set_extra_div(uint16_t extra_div) {
    if (extra_div > 0) {
        software_div = extra_div - 1;
    } else {
        software_div = 0;
    }
}

void timer::IRQHandler() {
    if (one_time_mode) {
        stop();
        one_time_mode = false;
    }

    static uint8_t count = 0;
    PWM->INTR |= 1u << to_underlying(timer_ident);

    if (count >= software_div) {
        if (callback) {
            callback();
        }
        count = 0;
    } else {
        count++;
    }
}
