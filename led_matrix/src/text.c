#include "text.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/sleep.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xil_printf.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xtime_l.h"
#include "led_matrix.h"
#include <stddef.h>

#define NUM_OF_ALPHABETS 25
#define NUM_OF_COLUMNS 6

typedef struct Mchar {
  uint64_t data;
  uint8_t width;
} Mchar;

static const Mchar mcharacters[NUM_OF_ALPHABETS] = {
    {0x000000003F48483F, 4}, // A
    {0x000000003649497F, 4}, // B
    {0x000000002241413E, 4}, // C
    {0x000000003E41417F, 4}, // D
    {0x000000004949497f, 4}, // E
    {0x000000004848487F, 4}, // F
    {0x000000002E49413E, 4}, // G
    {0x000000007F08087F, 4}, // H
    {0x0000000000417F41, 3}, // I
    {0x000000007E010106, 4}, // J
    {0x000000004122147F, 4}, // K
    {0x000000000101017F, 4}, // L
    {0x0000007F2010207F, 5}, // M
    {0x0000007F0408107F, 5}, // N
    {0x000000003E41413E, 4}, // O
    {0x000000003048487F, 4}, // P
    {0x000000003F43413E, 4}, // Q
    {0x00000000314A4C7F, 4}, // R
    {0x0000000026494932, 4}, // S
    {0x0000000000407F40, 3}, // T
    {0x000000007E01017E, 4}, // U
    {0x0000007C0201027C, 5}, // V
    {0x0000006314081463, 5}, // X
    {0x0000007008070870, 5}, // Y
    {0x0000006151494543, 5}, // Z
};
void write_alphabets() { write_mchar(); }

void write_mchar() {
  size_t i = 0;
  XTime start = 0;
  XTime end = 0;
  XTime_GetTime(&start);
  while (1) {
    uint64_t mchar_data = mcharacters[i].data;
    for (size_t j = 0; j < MTX_WIDTH; j++) {
      reset_matrix();
      size_t col = j < NUM_OF_COLUMNS ? j : 5;
      // uint8_t data = alphabets[i][col];
      uint8_t data = mchar_data & 0xFF;
      for (size_t k = 0; k < MTX_HEIGHT; k++) {
        for (size_t l = 0; l < MTX_COLORS; l++) {
          for (size_t m = 0; m < COLOR_BITS; m++) {
            if (m < 1)
              set_sda(data & 0x80);
            else
              set_sda(0x0);
            sck_cycle();
          }
        }
        data = data << 1;
      }
      // usleep(1000);
      set_channel(j);
      mchar_data = mchar_data >> 8;
      latch();
    }
    XTime_GetTime(&end);
    if (end - start > 200000000) {
      i++;
      XTime_GetTime(&start);
    }
    if (i == NUM_OF_ALPHABETS)
      i = 0;
    // xil_printf("end: %d start: %d\r\n", end, start);
    // sleep(1);
  }
}
