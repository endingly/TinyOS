#include <TinyOS/tty/tty.h>
#include <stdint-gcc.h>

#define TINYOS_TTY_WIDTH 80
#define TINYOS_TTY_HEIGHT 25

vga_atrributes* buffer      = 0xB8000;
vga_atrributes  theme_color = TINYOS_VGA_BLACK;
uint32_t        TTY_COLUMN  = 0;
uint32_t        TTY_ROW     = 0;

void tty_set_color(vga_atrributes fg, vga_atrributes bg) { theme_color = (fg << 4 | bg) << 8; }

void tty_push_char(char c) {
  *(buffer + TTY_COLUMN + TTY_ROW * TINYOS_TTY_WIDTH) = (theme_color | c);
  TTY_COLUMN++;
  if (TTY_COLUMN >= TINYOS_TTY_WIDTH) {
    TTY_COLUMN = 0;
    TTY_ROW++;
    if (TTY_ROW >= TINYOS_TTY_HEIGHT) {
      tty_scroll_up();
      TTY_ROW--;
    }
  }
}

void tty_scroll_up() {
  // [ ] TODO: implement this function
}

void tty_push_str(char* str) {
  while (*str != '\0') {
    tty_push_char(*str);
    str++;
  }
}

void tty_clear() {
  for (uint32_t x = 0; x < TTY_COLUMN; x++) {
    for (uint32_t y = 0; y < TTY_ROW; y++) {
      *(buffer + x + y * TINYOS_TTY_WIDTH) = (theme_color | ' ');
    }
  }
}