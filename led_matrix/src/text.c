#include "text.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/sleep.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xil_printf.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/xtime_l.h"
#include "led_matrix.h"
#include <stddef.h>

#define NUM_OF_ALPHABETS 94
#define NUM_OF_COLUMNS 6

typedef struct Mchar {
  uint64_t data;
  uint8_t width;
} Mchar;

static const Mchar mcharacters[NUM_OF_ALPHABETS] = {
    {0x0000000000000000, 5}, // space
    {0x00000000000000FA, 6}, // !
    {0x0000000000000000, 5}, // "
    {0x0000000000000000, 5}, // #
    {0x0000000000000000, 5}, // $
    {0x0000000000000000, 5}, // %
    {0x0000000000000000, 5}, // &
    {0x0000000000000000, 5}, // '
    {0x0000000000000000, 5}, // (
    {0x0000000000000000, 5}, // )
    {0x0000000000000000, 5}, // *
    {0x0000000000000000, 5}, // +
    {0x0000000000000003, 3}, // ,
    {0x0000000000000000, 5}, // -
    {0x0000000000000000, 5}, // .
    {0x0000000000000000, 5}, // /
    {0x0000000000000000, 5}, // @
    {0x0000000000000000, 5}, // 0
    {0x0000000000000000, 5}, // 1
    {0x0000000000000000, 5}, // 2
    {0x0000000000000000, 5}, // 3
    {0x0000000000000000, 5}, // 4
    {0x0000000000000000, 5}, // 5
    {0x0000000000000000, 5}, // 7
    {0x0000000000000000, 5}, // 8
    {0x0000000000000000, 5}, // 9
    {0x0000000000000000, 5}, // :
    {0x0000000000000000, 5}, // ;
    {0x0000000000000000, 5}, // <
    {0x0000000000000000, 5}, // =
    {0x0000000000000000, 5}, // >
    {0x0000000000000000, 5}, // ?
    {0x0000000000000000, 5}, // @
    {0x000000007C90907C, 5}, // A
    {0x000000006C9292FE, 5}, // B
    {0x000000004482827C, 5}, // C
    {0x00000000384482FE, 5}, // D
    {0x00000000929292FE, 5}, // E
    {0x00000000909090FE, 5}, // F
    {0x000000005C92827C, 5}, // G
    {0x00000000FE1010FE, 5}, // H
    {0x000000000082FE82, 4}, // I
    {0x00000000FC02020C, 5}, // J
    {0x00000000824428FE, 5}, // K
    {0x00000000020202FE, 5}, // L
    {0x000000FE402040FE, 6}, // M
    {0x000000FE081020FE, 6}, // N
    {0x000000007C82827C, 5}, // O
    {0x00000000609090FE, 5}, // P
    {0x000000007E86827C, 5}, // Q
    {0x00000000629498FE, 5}, // R
    {0x000000008C929264, 5}, // S
    {0x000000000080FE80, 4}, // T
    {0x00000000FC0202FC, 5}, // U
    {0x000000F8040204F8, 6}, // V
    {0x000000FE040804FE, 6}, // W
    {0x000000C6281028C6, 6}, // X
    {0x000000E0100D10E0, 6}, // Y
    {0x000000C2A2928A86, 6}, // Z
    {0x0000000000000000, 6}, // [
    {0x0000000000000000, 6}, // '\'
    {0x0000000000000000, 6}, // ]
    {0x0000000000000000, 6}, // ^
    {0x0000000000000000, 6}, // _
    {0x0000000000000000, 6}, // `
    {0x0000000000000000, 6}, // a
    {0x0000000000000000, 6}, // b
    {0x0000000000000000, 6}, // c
    {0x000000FE1222221C, 6}, // d
    {0x000000182A2A2A1C, 6}, // e
    {0x0000000000000000, 6}, // f
    {0x0000000000000000, 6}, // g
    {0x0000000000000000, 6}, // h
    {0x0000000000000000, 6}, // i
    {0x0000000000000000, 6}, // j
    {0x0000000000000000, 6}, // k
    {0x000000000002FE82, 5}, // l
    {0x0000000000000000, 6}, // m
    {0x0000000000000000, 6}, // n
    {0x000000001C22221C, 5}, // o
    {0x0000000000000000, 6}, // p
    {0x0000000000000000, 6}, // q
    {0x000000002020103E, 5}, // r
    {0x0000000000000000, 6}, // s
    {0x0000000000000000, 6}, // t
    {0x0000000000000000, 6}, // u
    {0x0000000000000000, 6}, // v
    {0x0000000000000000, 6}, // w
    {0x0000000000000000, 6}, // x
    {0x0000000000000000, 6}, // y
    {0x0000000000000000, 6}, // z
    {0x0000000000000000, 6}, // {
    {0x0000000000000000, 6}, // |
    {0x0000000000000000, 6}, // }
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

  char ttext[15] = "Hello World!";
  // char ttext[10] = "ABC";
  size_t len = 12;
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
      size_t mcidx = ttext[text_idx] - 0x20;
      mchar = mcharacters[mcidx];
      // size_t mcol = i;
      uint8_t col_data =
          (text_idx < len) ? (mchar.data >> (mchar_col * 8)) & 0xFF : 0x0;
      // col_data = col_data << 1;
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
    if (end - start > 90000000) {
      // if (end - start > 30000000) {
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
