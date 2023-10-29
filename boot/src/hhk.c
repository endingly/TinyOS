#include <boot/idt.h>
#include <boot/multiboot.h>
#include <stdint-gcc.h>

typedef unsigned int ptd_t;

#define PAGE_TABLE_ADDR(ptd, pt_index)         ((ptd_t*)ptd + (pt_index + 1) * 1024)
#define SET_PDE(ptd, pde_index, pde)           *((ptd_t*)ptd + pde_index) = pde;
#define SET_PTE(ptd, pt_index, pte_index, pte) *(PAGE_TABLE_ADDR(ptd, pt_index) + pte_index) = pte;
#define sym_val(sym)                           ((uintptr_t) & sym)

#define KERNEL_PAGE_COUNT (sym_val(__kernel_end) - sym_val(__kernel_start) + 0x1000 - 1)
#define HHK_PAGE_COUNT    ((sym_val(__hhk_end) - 0x100000 + 0x1000 - 1) >> 12)
#define PG_TABLE_IDENTITY 0  // table #1
#define PG_TABLE_KERNEL   1  // table #2 - #4
#define PG_TABLE_STACK    4  // table #5

/* 由链接脚本提供 */
extern uint8_t __kernel_start;
extern uint8_t __kernel_end;
extern uint8_t __init_hhk_end;
extern uint8_t __k_stack;

void _init_page(ptd_t* t) {
  SET_PDE(t, 0, 0x00000003);  // 0x00000000 - 0x003fffff
}