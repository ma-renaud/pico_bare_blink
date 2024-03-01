#include "reset.h"
#include "rp2040.h"
#include "utils.h"

static inline void reset_block(uint32_t bits) {
  RESETS->reset |= bits;

}

static inline void unreset_block(uint32_t bits) {
  RESETS->reset &= ~bits;
}

static inline void unreset_block_wait(uint32_t bits) {
  RESETS->reset &= ~bits;
  while (!(RESETS->reset_done & bits)) {
  }
}

void reset(Peripherals periph) {
  unreset_block_wait(to_underlying(periph));
}