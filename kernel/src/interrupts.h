#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "registers.h"

//TODO: Handle other architectures
typedef struct interrupt_stack_frame{
    uint32_t flags;
    uint32_t cs;
    union{
        uint32_t eip;
        struct{
            uint16_t lip;
            uint16_t hip;
        };
    };
}__attribute__((packed)) interrupt_stack_frame;

typedef struct interrupt_registers_t{
    general_registers_t cpu_registers;
    uint32_t interrupt_number;
}__attribute__((packed)) interrupt_registers_t;

#define IRQ_BEGIN 32

bool are_interrupts_enabled();
bool enable_interrupts();
bool disable_interrupts();
void khalt();

void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();
void spurious_interrupt();
void interrupt_exception();

// Called from the isr after necessary values are pushed onto stack
void interrupt_handler(interrupt_registers_t* registers);

// Installs an interupt handler for each interrupt request line(not number)
void irq_install_handler(int irq_line, void (*handler)(general_registers_t*));
// Installs an exception handler for interrupts 0-31
void irq_install_exception_handler(int exception, void (*handler)(general_registers_t*));

extern void interrupt_test();
#endif
