#pragma once
// 参考资料: Intel Manul Vol.3 TABLE 6-1

#define FAULT_DIVIDE_ERROR         0x00
#define FAULT_TRAP_DEBUG_EXCEPTION 0x01
#define INTERRUPT_NMI              0x02
#define TRAP_BREAKPOINT            0x03
#define TRAP_OVERFLOW              0x04
#define FAULT_BOUND_RANGE          0x05
#define FAULT_INVALID_OPCODE       0x06
#define FAULT_DEVICE_NOT_AVAILABLE 0x07
#define ABORT_DOUBLE_FAULT         0x08
#define FAULT_COPROCESSOR_OVERRUN  0x09
#define FAULT_INVALID_TSS          0x0A
#define FAULT_SEGMENT_NOT_PRESENT  0x0B
#define FAULT_STACK_SEGMENT_FAULT  0x0C
#define FAULT_GENERAL_PROTECTION   0x0D
#define FAULT_PAGE_FAULT           0x0E
#define FAULT_RESERVED_NOT_USED    0x0F
#define FAULT_X87_FLOATING_POINT   0x10
#define FAULT_ALIGNMENT_CHECK      0x11
#define ABORT_MACHINE_CHECK        0x12
#define FAULT_SIMD_FLOATING_POINT  0x13
#define FAULT_VIRTUALIZATION       0x14
#define FAULT_CONTROL_PROTECTION   0x15

// 系统预留的 32 个位置中，只用了前 21 个，剩下的用户可自定义
#pragma pack(1)
typedef struct _interrupt_parma {
  unsigned int   vector;
  unsigned int   error_code;
  unsigned int   eip;
  unsigned short cs;
  unsigned int   eflags;
} interrupt_parma;
#pragma pack()

void interrupt_handle(interrupt_parma *parma);
