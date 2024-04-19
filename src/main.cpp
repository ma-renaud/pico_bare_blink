#include "clocks.h"
#include "gpio.h"
#include "isr_vectors.h"
#include "reset.h"
#include "timer.h"

static constexpr uint8_t led_io = 25;
static constexpr uint16_t timer_period = 65195;
static constexpr uint8_t timer_div = 255;
static constexpr uint8_t timer_extra_div = 8;
static constexpr uint8_t timer_interrupt_priority = 0;

namespace {
gpio led;
timer led_timer(timer::ident::timer0);
} // namespace

void init();
[[noreturn]] void loop();
void timer0_callback();

int main() {
    init();
    loop();
    return 0;
}

void init() {
    // Reset peripheral
    reset::reset(reset::Peripherals::bus_ctrl);
    reset::reset(reset::Peripherals::io_bank0);
    reset::reset(reset::Peripherals::pwm);

    // Configure led
    led.init(led_io, gpio_mode::GPIO);

    // Configure timer
    led_timer.init(timer_period, timer_div);
    led_timer.set_extra_div(timer_extra_div);
    led_timer.enable_interrupts(timer_interrupt_priority);
    led_timer.register_callback(timer0_callback);
    registerHandler(PWM_IRQ_WRAP_IRQn, [tim = &led_timer]() { tim->IRQHandler(); });
    led_timer.start();
}

void loop() {
    while (true) {}
}

void timer0_callback() {
    led.toggle();
}
