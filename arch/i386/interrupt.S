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
        push %eax

        call interrupt_handler
        add $0x4, %esp
        iret