#ifndef TIMER_H
#define TIMER_H

#include "i_timer.h"

class timer : public i_timer {
public:
    enum class ident : uint8_t {
        timer0,
        timer1,
        timer2,
        timer3,
        timer4,
        timer5,
        timer6,
        timer7,
        timer_none,
    };

    timer(timer::ident timer_ident);
    ~timer() = default;

    void init(uint16_t period, uint8_t prescaler) override;
    void start() override;
    void start_one_time() override;
    void stop() override;
    void register_callback(std::function<void()> &&function) override;

    void enable_interrupts(uint32_t priority);
    void set_extra_div(uint16_t extra_div);

    void IRQHandler();

private:
    std::function<void()> callback{nullptr};
    bool one_time_mode{false};
    timer::ident timer_ident{ident::timer_none};
    uint16_t software_div{0};
};

#endif // TIMER_H
