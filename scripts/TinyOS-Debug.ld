ENTRY(start_)
SECTIONS {
    . = 0x100000;
    /* 高半核代码段与数据段初始化 */
    .hhk_init_text BLOCK(4K) : {
        * (.multiboot)
        libboot.a (.hhk_init)
        libboot.a (.text)
    }

    .hhk_init_bss BLOCK(4K) : {
        libboot.a (.bss)
    }

    .hhk_init_data BLOCK(4K) : {
        libboot.a (.data)
    }

    .hhk_init_rodata BLOCK(4K) : {
        libboot.a (.rodata)
    }
    __init_hhk_end = ALIGN(4K);

    /* 将内核重新分布至内存 3GB 之后的空间 */
    . += 0xC0000000;

    .text BLOCK(4K) : AT(ADDR(.text) - 0xC0000000) {
        kernel.bin (.text)
        libhal.a (.text)
    }
    .bss BLOCK(4K) : AT(ADDR(.bss) - 0xC0000000) {
        kernel.bin (.bss)
        libhal.a (.bss)
    }
    .data BLOCK(4K) : AT(ADDR(.data) - 0xC0000000) {
        kernel.bin (.data)
        libhal.a (.data)
    }
    .rodata BLOCK(4K) : AT(ADDR(.rodata) - 0xC0000000) {
        kernel.bin (.rodata)
        libhal.a (.rodata)
    }
    .kpg BLOCK(4K) : AT(ADDR(.kpg) - 0xC0000000) {
        libboot.a (.kpg)
    }  
    _kernel_end = ALIGN(4K);
    _heap_start = ALIGN(4K);    /* 内核结束，堆起始地址 */
}