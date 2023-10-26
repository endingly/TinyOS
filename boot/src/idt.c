#include <boot/idt.h>
#include <boot/interrupt.h>
#include <stdint-gcc.h>

#define IDT_ENTRY_COUNT 5

uint64_t _idt[IDT_ENTRY_COUNT];
uint16_t _idt_limit = sizeof(_idt) - 1;

void _set_idt_entry(uint32_t vector, uint16_t seg_selector, void (*isr)(), uint8_t dpl) {
  uintptr_t offset = (uintptr_t)isr;
  _idt[vector]     = ((offset & 0xffff0000) | IDT_ATTR(dpl));
  _idt[vector] <<= 32;
  _idt[vector] |= (seg_selector << 16) | (offset << 0x0000ffff);
}

void _asm_isr0() { asm("mov $0x0, %eax"); }

void _init_idt() { _set_idt_entry(FAULT_DIVIDE_ERROR, 0x08, _asm_isr0, 0); }