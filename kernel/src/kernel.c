#include <boot/gdt.h>
#include <boot/idt.h>
#include <kernel/tty/tty.h>

void _kernel_init() {
  _init_gdt();
  _init_idt();
}

void _kernel_main(void* info_table) {
  tty_set_color(TINYOS_VGA_WHITE, TINYOS_VGA_BLACK);
  tty_push_str("Hello TinyOS!\n");
  tty_push_str("This is a test string.\n");
  asm("int $0");
}