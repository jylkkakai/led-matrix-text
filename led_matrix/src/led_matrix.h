#ifndef LED_MATRIX_
#define LED_MATRIX_

#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xparameters.h"
#include <stdint.h>

#define BTNS_BASEADDR XPAR_AXI_GPIO_BTNS_BASEADDR
#define LEDS_BASEADDR XPAR_AXI_GPIO_LEDS_BASEADDR
#define MTX_CTRL_BASEADDR XPAR_AXI_GPIO_MTX_CTRL_BASEADDR
#define RGB_LEDS_BASEADDR XPAR_AXI_GPIO_RGB_LEDS_BASEADDR
#define SWS_BASEADDR XPAR_AXI_GPIO_SWS_BASEADDR
#define MTX_WIDTH 8
#define MTX_HEIGHT 8
#define MTX_COLORS 3
#define COLOR_BITS 8

uint8_t get_switches();
uint8_t get_buttons();
void set_leds(uint8_t value);
void set_rgb_leds(uint8_t value);
void set_sda(uint8_t value);
void sck_cycle();
void set_sb(uint8_t value);
void latch();
void set_rstn(uint8_t value);
void set_channel(uint8_t value);
void reset_matrix();

#endif // !LED_MATRIX_
