#include "interrupts.h"
#include "io.h"
#include "i8259.h"
#include "drivers/keyboard.h"
#include "registers.h"

static void(*irqs[16])(general_registers_t*)={0};

void interrupt_handler(interrupt_registers_t* interrupt_registers){
    uint8_t irq_line = interrupt_registers->interrupt_number;
    if(irq_line == 255){
        // Spurious/unsupported interrupt
        return;
    }
    if(irq_line < 32){
        kprintf("Unsupported cpu exception %d\n", irq_line);
        return;
    }
    if(irq_line < IRQ_BEGIN || irq_line >= IRQ_BEGIN + 16){
        // Spurious interrupt
        return;
    }
    // TODO: handle spurious interrupts, NMI, and exceptions
    void (*handler)(general_registers_t* registers) = irqs[irq_line - IRQ_BEGIN];
    if(!handler){
        kprintf("Warning. Unsupported interrupt %u\n", irq_line);
        i8259_send_eoi(irq_line);
        return;
    }
    handler(&interrupt_registers->cpu_registers);

    i8259_send_eoi(interrupt_registers->interrupt_number);
}
void interrupt_exception_handler(general_registers_t registers){
    kprintf("exception caught\n");
}

void irq_install_handler(int irq_line, void (*handler)(general_registers_t*)){
    irqs[irq_line] = handler;
}
