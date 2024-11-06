#include "text.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/sleep.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xil_printf.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xtime_l.h"
#include "led_matrix.h"
#include <stddef.h>

#define NUM_OF_ALPHABETS 26
#define NUM_OF_COLUMNS 6

typedef struct Mchar {
  uint64_t data;
  uint8_t width;
} Mchar;

static const Mchar mcharacters[NUM_OF_ALPHABETS] = {
    {0x000000003F48483F, 5}, // A
    {0x000000003649497F, 5}, // B
    {0x000000002241413E, 5}, // C
    {0x000000003E41417F, 5}, // D
    {0x000000004949497f, 5}, // E
    {0x000000004848487F, 5}, // F
    {0x000000002E49413E, 5}, // G
    {0x000000007F08087F, 5}, // H
    {0x0000000000417F41, 4}, // I
    {0x000000007E010106, 5}, // J
    {0x000000004122147F, 5}, // K
    {0x000000000101017F, 5}, // L
    {0x0000007F2010207F, 6}, // M
    {0x0000007F0408107F, 6}, // N
    {0x000000003E41413E, 5}, // O
    {0x000000003048487F, 5}, // P
    {0x000000003F43413E, 5}, // Q
    {0x00000000314A4C7F, 5}, // R
    {0x0000000026494932, 5}, // S
    {0x0000000000407F40, 4}, // T
    {0x000000007E01017E, 5}, // U
    {0x0000007C0201027C, 6}, // V
    {0x0000007F0204027F, 6}, // W
    {0x0000006314081463, 6}, // X
    {0x0000007008070870, 6}, // Y
    {0x0000006151494543, 6}, // Z
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
  }
}

void scrolling_print(char *text) {

  char ttext[10] = "HELLOWORLD";
  // char ttext[10] = "ABC";
  size_t len = 10;
  size_t start_text_idx = 0;
  // size_t text_idx = 0;
  int start_mchar_col = 0;
  // int mchar_col = 0;
  Mchar mchar; // = {0x0000000000000000, 8};

  XTime start = 0;
  XTime end = 0;
  XTime_GetTime(&start);

  while (1) {
    int mchar_col = start_mchar_col;
    int text_idx = start_text_idx;

    for (size_t i = 0; i < MTX_WIDTH; i++) {
      size_t mcidx = ttext[text_idx] - 0x41;
      mchar = mcharacters[mcidx];
      // size_t mcol = i;
      uint8_t col_data =
          (text_idx < len) ? (mchar.data >> (mchar_col * 8)) & 0xFF : 0x0;
      for (size_t j = 0; j < MTX_HEIGHT; j++) {
        for (size_t k = 0; k < MTX_COLORS; k++) {
          for (size_t l = 0; l < COLOR_BITS; l++) {
            // if (start_pos >= 0 && tidx < len)
            set_sda(col_data & 0x80);
            // else
            //   set_sda(0x0);
            sck_cycle();
          }
        }
        col_data = col_data << 1;
      }
      mchar_col++;
      usleep(1000);
      if (mchar_col == mchar.width) {
        // text_idx++;
        text_idx = text_idx == len ? 0 : text_idx + 1;
        mchar_col = 0;
      }
      set_channel(i);
      // mchar_data = mchar_data >> 8;
      latch();
    }
    XTime_GetTime(&end);
    if (end - start > 30000000) {
      start_mchar_col++;
      if (start_mchar_col == mcharacters[start_text_idx].width) {
        start_text_idx++;
        start_mchar_col = 0;
      }
      if (start_text_idx == len) {
        start_text_idx = 0;
        start_mchar_col = 0;
      }
      // i++;
      XTime_GetTime(&start);
    }
    // if (i == NUM_OF_ALPHABETS)
    //   i = 0;
  }
}
