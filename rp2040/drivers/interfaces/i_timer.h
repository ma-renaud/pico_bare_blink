#ifndef I_TIMER_H
#define I_TIMER_H

#include <cstdint>
#include <functional>

class i_timer {
public:
    virtual void init(uint16_t period, uint8_t prescaler) = 0;
    virtual void start() = 0;
    virtual void start_one_time() = 0;
    virtual void stop() = 0;
    virtual void register_callback(std::function<void()> &&f) = 0;
};

#endif // I_TIMER_H
