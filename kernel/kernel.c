#include <TinyOS/tty/tty.h>

void _kernel_init() {}

void _kernel_main(void* info_table) {
  tty_set_color(TINYOS_VGA_WHITE, TINYOS_VGA_BLACK);
  tty_push_str("Hello TinyOS!\n");
  tty_push_str("This is a test string.\n");
}