#include <TinyOS/arch/i386/multiboot.h>
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
    .type start_, @function
    start_:
        movl $stack_top, %esp
        /* [ ] kernel init
               [x]. load GDT
               2. load IDT
               3. enable paging
        */
        call _kernel_init
        subl $0x6, %esp
        movl $_gdt, 2(%esp)
        movw _gdt_limit, %ax
        movw %ax, (%esp)
        lgdt (%esp)
        addl $0x6, %esp

        movw $0x10, %cx
        movw %cx, %es
        movw %cx, %ds
        movw %cx, %fs
        movw %cx, %gs
        movw %cx, %ss
        
        pushw $0x08
        pushl $_after_gdt
        retf
    _after_gdt:
        pushl %ebx
        call _kernel_main

        cli
    j_:
        hlt
        jmp j_
        