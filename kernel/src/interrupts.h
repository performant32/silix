#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "registers.h"

extern bool are_interrupts_enabled();
extern bool enable_interrupts();
extern bool disable_interrupts();
extern void khalt();

extern void isr_wrapper();
extern void interrupt_fault_wrapper();
extern void interrupt_trap_wrapper();
extern void interrupt_abort_wrapper();

void interrupt_handler(registers_t registers);
void interrupt_fault_handler(registers_t registers);
void interrupt_trap_handler(registers_t registers);
void interrupt_abort_handler(registers_t registers);

extern void interrupt_test();
#endif
