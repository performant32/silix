#ifndef INTERRUPTS_H
#define INTERRUPTS_H

extern bool are_interrupts_enabled();
extern bool enable_interrupts();
extern bool disable_interrupts();
extern void khalt();
extern void isr_wrapper();
void interrupt_handler();
#endif
