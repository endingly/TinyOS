#include <kernel/interrupt/interrupt.h>
#include <kernel/tty/tty.h>

void isr0(interrupt_parma* parma) {
  tty_clear();
  tty_push_str("!!PANIC!!\n");
}

/// @brief 硬件中断入口
/// @param parma 中断寄存器结构体，存储各类信息
void interrupt_handle(interrupt_parma* parma) {
  tty_push_str("!!Exception!!");
  switch (parma->vector) {
    case 0:
      isr0(parma);
      break;
  }
}