#ifndef LED_MATRIX_
#define LED_MATRIX_

#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xparameters.h"
#include <stdint.h>

#define BTNS_BASEADDR XPAR_AXI_GPIO_BTNS_BASEADDR
#define LEDS_BASEADDR XPAR_AXI_GPIO_LEDS_BASEADDR
#define MTX_CTRL_BASEADDR XPAR_AXI_GPIO_MTX_CTRL_BASEADDR
#define RGB_LEDS_BASEADDR XPAR_AXI_GPIO_RGB_LEDS_BASEADDR
#define SWS_BASEADDR XPAR_AXI_GPIO_SWS_BASEADDR

uint8_t get_switches();
uint8_t get_buttons();
void set_leds(uint8_t value);
void set_rgb_leds(uint8_t value);
void set_sda(uint8_t value);
void set_sck(uint8_t value);
void set_sb(uint8_t value);
void set_lat(uint8_t value);
void set_rstn(uint8_t value);

#endif // !LED_MATRIX_
