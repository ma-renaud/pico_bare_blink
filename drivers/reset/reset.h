#ifndef RESET_H
#define RESET_H

#include "rp2040.h"

static inline void reset_block(uint32_t bits) {
    //hw_set_bits(RESETS->reset, bits);
    RESETS->reset |= bits;

}

static inline void unreset_block(uint32_t bits) {
    //hw_clear_bits(&resets_hw->reset, bits);
    RESETS->reset &= ~bits;
}

static inline void unreset_block_wait(uint32_t bits) {
    RESETS->reset &= ~bits;
    while (!(RESETS->reset_done & bits)) {}
}

#endif //RESET_H
