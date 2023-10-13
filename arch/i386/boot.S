#include "multiboot.h"
.code32

.section .multiboot
    .long TINYOS_MULTIBOOT_MAGIC
    .long TINYOS_MULTIBOOT_FLAG_4KB_ALIGNED_MEM_MAP
    .long TINYOS_CHECKSUM(TINYOS_MULTIBOOT_FLAG_4KB_ALIGNED_MEM_MAP)

.section .bss
    /* According to system V abi */
    .align 16
    stack_bottom:
        .skip 16318, 0  /* 16 KB */
    stack_top:

.section .text
    .global start_
    start_:
        mov $stack_top, %esp
        /* [ ] kernel init
               1. load GDT
               2. load IDT
               3. enable paging
        */
        call _kernel_init

        push %ebx
        call _kernel_main

        cli
    j_:
        hlt
        jmp j_
        