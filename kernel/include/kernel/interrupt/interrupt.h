#pragma once
#pragma pack(push, 1)
typedef struct _interrupt_parma {
  unsigned int   vector;
  unsigned int   error_code;
  unsigned int   eip;
  unsigned short cs;
  unsigned int   eflags;
} interrupt_parma;
#pragma pack(pop)

void _asm_isr0();

void interrupt_handle(interrupt_parma *parma);
