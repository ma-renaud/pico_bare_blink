#include "reset.h"
#include "rp2040.h"
#include "utils.h"
#include "clocks.h"

namespace reset {

static inline void reset_block(uint32_t bits) {
    RESETS->reset |= bits;
}

static inline void unreset_block_wait(uint32_t bits) {
    RESETS->reset &= ~bits;
    while ((RESETS->reset_done & bits) == 0) {}
}

void reset(Peripherals periph) {
    if (periph == Peripherals::clocks) {
        clocks::reset();
    } else {
        reset_block(to_underlying(periph));
        unreset_block_wait(to_underlying(periph));
    }
}

} // namespace reset