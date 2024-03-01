#ifndef RESET_H
#define RESET_H

#include "cstdint"

enum class Peripherals : uint32_t {
  adc = 0x00000001,
  bus_ctrl = 0x00000002,
  dma = 0x00000004,
  i2c0 = 0x00000008,
  i2c1 = 0x00000010,
  io_bank0 = 0x00000020,
  io_qspi = 0x00000040,
  jtag = 0x00000080,
  pads_bank0 = 0x00000100,
  pads_qspi = 0x00000200,
  pio0 = 0x00000400,
  pio1 = 0x00000800,
  pll_sys = 0x00001000,
  pll_usb = 0x00002000,
  pwm = 0x00004000,
  rtc = 0x00008000,
  spi0 = 0x00010000,
  spi1 = 0x00020000,
  sys_cfg = 0x00040000,
  sys_info = 0x00080000,
  tbman = 0x00100000,
  timer = 0x00200000,
  uart0 = 0x00400000,
  uart1 = 0x00800000,
  usb_crtl = 0x01000000,

};

void reset(Peripherals periph);

#endif //RESET_H
