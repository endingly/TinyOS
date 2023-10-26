// 利用汇编包装函数，等待链接器调用即可
.macro isr_template vector,no_error_code=1
    .global _asm_isr\vector
    .type _asm_isr\vector, @function
    _asm_isr\vector:
        .if \no_error_code
            push $0x0
        .endif
        push $\vector
        jmp interrupt_wrapper
.endm

.section .text
    isr_template 0
    interrupt_wrapper:
        mov %esp, %eax
        and $0xfffffff0, %esp
        sub $16, %esp
        mov %eax, (%esp)

        call interrupt_handle
        pop %eax
        mov %eax, %esp
        add $0x4, %esp
        iret