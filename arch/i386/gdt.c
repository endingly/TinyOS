#include <TinyOS/arch/i386/gdt.h>
#include <stdint-gcc.h>

#define GDT_ENTRY_COUNT 5

uint64_t _gdt[GDT_ENTRY_COUNT];
uint16_t _gdt_limit = sizeof(_gdt) - 1;

void _set_gdt_entry(uint32_t index, uint32_t base, uint32_t limit, uint32_t flag) {
  _gdt[index] = SD_BASE_HIGH(base) | flag | SD_LIM_HIGH(limit) | SD_BASE_MID(base);
  _gdt[index] <<= 32;
  _gdt[index] |= SD_BASE_LOW(base) | SD_LIM_LOW(limit);
}

void _init_gdt() {
  _set_gdt_entry(0, 0, 0, 0);
  _set_gdt_entry(1, 0, 0xfffff, GDT_CODE_PL0);
  _set_gdt_entry(2, 0, 0xfffff, GDT_DATA_PL0);
  _set_gdt_entry(3, 0, 0xfffff, GDT_CODE_PL3);
  _set_gdt_entry(4, 0, 0xfffff, GDT_DATA_PL3);
}