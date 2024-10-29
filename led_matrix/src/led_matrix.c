#include "led_matrix.h"

uint8_t get_switches() { return *(uintptr_t *)(SWS_BASEADDR); }
uint8_t get_buttons() {
  // uintptr_t *btns = (uintptr_t *)BTNS_BASEADDR;
  // return *btns;
  return *(uintptr_t *)BTNS_BASEADDR;
}
void set_leds(uint8_t value) { *(uintptr_t *)(LEDS_BASEADDR) = value; }
void set_rgb_leds(uint8_t value) { *(uintptr_t *)(RGB_LEDS_BASEADDR) = value; }
void set_sda(uint8_t value) {

  uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
  if (value)
    *ctrl |= 0x1;
  else
    *ctrl &= ~0x1;
}
void set_sck(uint8_t value) {
  uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
  if (value)
    *ctrl |= 0x2;
  else
    *ctrl &= ~0x2;
}
void set_sb(uint8_t value) {
  uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
  if (value)
    *ctrl |= 0x4;
  else
    *ctrl &= ~0x4;
}
void set_lat(uint8_t value) {
  uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
  if (value)
    *ctrl |= 0x8;
  else
    *ctrl &= ~0x8;
}
void set_rstn(uint8_t value) {
  uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
  if (value)
    *ctrl |= 0x10;
  else
    *ctrl &= ~0x10;
}
