#ifndef TEXT_H_
#define TEXT_H_
#include <stdint.h>
#define MCHAR_COLS 6

// typedef uint8_t (*matrix_char)[MCHAR_COLS];
// const matrix_char get_mchar(const char achar);
void write_mchar();
void write_alphabets();
void scrolling_print(char *text);
#endif // TEXT_H_
