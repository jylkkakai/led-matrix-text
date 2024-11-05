#include "led_matrix.h"
#include "assert.h"

uint8_t get_switches() { return *(uintptr_t *)(SWS_BASEADDR); }
uint8_t get_buttons() { return *(uintptr_t *)BTNS_BASEADDR; }
void set_leds(uint8_t value) { *(uintptr_t *)(LEDS_BASEADDR) = value; }
void set_rgb_leds(uint8_t value) { *(uintptr_t *)(RGB_LEDS_BASEADDR) = value; }
void set_sda(uint8_t value) {
  uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
  if (value)
    *ctrl |= 0x200;
  else
    *ctrl &= ~0x200;
}
void sck_cycle() {
  uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
  *ctrl |= 0x100;
  *ctrl &= ~0x100;
}
void set_sb(uint8_t value) {
  uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
  if (value)
    *ctrl |= 0x400;
  else
    *ctrl &= ~0x400;
}
void latch() {
  uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
  *ctrl |= 0x800;
  *ctrl &= ~0x800;
}
void set_rstn(uint8_t value) {
  uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
  if (value)
    *ctrl |= 0x1000;
  else
    *ctrl &= ~0x1000;
}
void set_channel(uint8_t value) {
  assert(value < 8 & value >= 0);
  uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
  *ctrl &= ~0xff;
  *ctrl |= 1 << value;
}
