#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "registers.h"

typedef struct interrupt_registers_t{
    registers_t cpu_registers;
    uint32_t interrupt_number;
}__attribute__((packed)) interrupt_registers_t;

#define IRQ_BEGIN 32

extern bool are_interrupts_enabled();
extern bool enable_interrupts();
extern bool disable_interrupts();
extern void khalt();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
extern void spurious_interrupt();

void interrupt_handler(interrupt_registers_t* registers);
void irq_install_handler(int irq_line, void (*handler)(registers_t*));

extern void interrupt_test();
#endif
