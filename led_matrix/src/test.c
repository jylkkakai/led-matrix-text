#include "test.h"
#include "../../led_matrix_bsp/ps7_cortexa9_0/include/sleep.h"
#include "led_matrix.h"
#include <stdint.h>

static uint8_t matrix[WIDTH][HEIGHT][COLORS];
//
// void reset_matrix() {
//   volatile uintptr_t *ctrl = (uintptr_t *)MTX_CTRL_BASEADDR;
//   const size_t bits = 24 * 6;
//
//   set_rstn(1);
//   set_sb(0);
//   // *ctrl = 1;
//   // Set brightness to 1 for all channels
//   for (size_t i = 0; i < bits; i++) {
//     set_sda(1);
//     sck_cycle();
//     // *ctrl_addr &= ~0x8;
//     // *ctrl_addr |= 0x10;
//     // *ctrl_addr |= 0x8;
//   }
//   latch();
//   // *ctrl_addr |= 0x2;
//   // *ctrl_addr &= ~0x2;
//   set_sb(1);
//   // *ctrl_addr |= 0x4;
// }

// void set_pixel(uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
//
//   volatile int *ctrl_addr = (int *)CTRL_ADDR;
//   uint8_t col[HEIGHT][COLORS] = {0};
//   col[y][0] = b;
//   col[y][1] = g;
//   col[y][2] = r;
//   for (size_t i = 0; i < HEIGHT; i++) {
//     for (size_t j = 0; j < COLORS; j++) {
//       uint8_t data = col[i][j];
//       for (size_t k = 0; k < 8; k++) {
//         if (data & 0x80)
//           *ctrl_addr |= 0x10;
//         else
//           *ctrl_addr &= ~0x10;
//
//         *ctrl_addr &= ~0x8;
//         data = data < 1;
//         *ctrl_addr |= 0x8;
//       }
//     }
//   }
//   *ctrl_addr |= 0x2;
//   *ctrl_addr &= ~0x2;
// }
//
// void set_matrix() {
//
//   volatile int *col_addr = (int *)COL_ADDR;
//   *col_addr = 0x8;
//   set_pixel(1, 0xff, 0x0, 0x0);
// }
//
// void set_all() {
//   volatile int *ctrl_addr = (int *)CTRL_ADDR;
//   volatile int *col_addr = (int *)COL_ADDR;
//   *col_addr = 0x0;
//   *ctrl_addr |= 0x4;
//   for (size_t i = 0; i < 8; i++) {
//     for (size_t j = 0; j < HEIGHT * COLORS; j++) {
//       *ctrl_addr &= ~0x8;
//       *ctrl_addr |= 0x10;
//       *ctrl_addr |= 0x8;
//     }
//     *col_addr = (1 << i);
//     // *col_addr = pow(2, i);
//     *ctrl_addr |= 0x2;
//     *ctrl_addr &= ~0x2;
//     // sleep(1);
//   }
//   // *ctrl_addr |= 0x2;
//   // *ctrl_addr &= ~0x2;
// }

// void test(int col) {
//   volatile int *ctrl_addr = (int *)CTRL_ADDR;
//   volatile int *col_addr = (int *)COL_ADDR;
//   *col_addr = col;
//   *ctrl_addr |= 0x4;
//   for (size_t i = 0; i < 24 * 8; i++) {
//     *ctrl_addr &= ~0x8;
//     *ctrl_addr |= 0x10;
//     *ctrl_addr |= 0x8;
//   }
//   *ctrl_addr |= 0x2;
//   *ctrl_addr &= ~0x2;
// }

void test_btns_sws() {
  uint8_t counter;
  while (1) {
    uint8_t btns = get_buttons();
    uint8_t sws = get_switches();
    if (btns || sws) {
      set_leds(counter);
      set_rgb_leds(counter);
      counter += 1;
    }
    // sleep(1);
    usleep(500000);
  }
}

void test_leds() { set_leds(0xf); }

void test() {

  set_channel(2);
  for (size_t k = 0; k < 24 * 8; k++) {
    set_sda(1);
    sck_cycle();
  }
  latch();
}

void set_pixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
  memset(&matrix, 0, sizeof(matrix));
  matrix[x][y][0] = b;
  matrix[x][y][1] = g;
  matrix[x][y][2] = r;
}

void write_matrix() {
  for (size_t i = 0; i < WIDTH; i++) {
    set_channel(i);
    for (size_t j = 0; j < HEIGHT; j++) {
      for (size_t k = 0; k < COLORS; k++) {
        uint8_t data = matrix[i][j][k];
        for (size_t k = 0; k < 8; k++) {
          set_sda(data & 0x80);
          data = data << 1;
          sck_cycle();
        }
      }
    }
    latch();
  }
}

void test_matrix() {

  // set_rstn(1);
  // set_channel(2);
  size_t j = 0;
  while (1) {
    for (size_t i = 0; i < HEIGHT; i++) {
      set_pixel(1, 2, 0xff, 0x0, 0x0);
      write_matrix();
      // usleep(100000);
    }
  }
}
