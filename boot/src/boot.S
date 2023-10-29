#include <boot/multiboot.h>
.code32

#define MB_FLAG TINYOS_MULTIBOOT_FLAG_4KB_ALIGNED_MEM_MAP | TINYOS_MULTIBOOT_PAGE_ALIGN
#define KPG_SIZE 24*1024


.section .multiboot
    .long TINYOS_MULTIBOOT_MAGIC
    .long MB_FLAG
    .long TINYOS_CHECKSUM(MB_FLAG)

.section .bss
    .global mb_info
    /* According to system V abi */
    .align 16
    /* 为 multiboot mem struct info 预留空间 */
    mb_info:
        .skip 4096
    stack_bottom:
        .skip 16318, 0  /* 16 KB */
    stack_top:

.section .kpg
    .global _k_ptd
    _k_ptd:
        .skip KPG_SIZE, 0

.section .hhk_init
    .global start_
    .type start_, @function
    start_:
        mov $stack_top, %esp
        sub $16, %esp

        mov $mb_info, 4(%esp)
        mov %ebx, %esp
        call _save_multiboot_info

        mov $(KPG_SIZE), 4(%esp)
        mov $(_k_ptd - 0xC0000000), %esp
        call hhk_init

        /* 加载 PTD 基地址 */
        mov %esp, %eax
        and $0xFFFFF000, %eax
        mov %eax, %cr3

        /* 开启分页与地址转换 CR0.PG=1 */
        mov %cr0, %eax
        or $0x80000000, %eax
        mov %eax, %cr0

        add $16, %esp

        /* 进入内核 */
        push $hhk_entry_
        ret
        