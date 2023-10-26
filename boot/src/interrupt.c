#include <boot/interrupt.h>
#include <kernel/tty/tty.h>


void isr0(interrupt_parma* parma) {
  tty_clear();
  tty_push_str("!!PANIC!!\n");
}

void interrupt_handle(interrupt_parma* parma) {
  switch (parma->vector) {
    case 0:
      isr0(parma);
      break;
    default:
      break;
  }
}