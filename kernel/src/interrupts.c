#include "interrupts.h"
#include "io.h"
#include "i8259.h"
#include "drivers/keyboard.h"
#include "registers.h"

static void(*irqs[16])(general_registers_t*)={0};

void interrupt_handler(interrupt_registers_t* interrupt_registers){
    uint8_t irq = interrupt_registers->interrupt_number;
    if(irq == 255){
        // Spurious/unsupported interrupt
        return;
    }
    if(irq < 32){
        kprintf("Unsupported cpu exception %d\n", irq);
        return;
    }
    if(irq < IRQ_BEGIN || irq >= IRQ_BEGIN + 16){
        // Spurious interrupt
        return;
    }
    // TODO: handle spurious interrupts, NMI, and exceptions
    void (*handler)(general_registers_t* registers) = irqs[irq - IRQ_BEGIN];
    if(!handler){
        kprintf("Warning. Unsupported interrupt %u\n", irq);
        i8259_send_eoi(irq);
        return;
    }
    handler(&interrupt_registers->cpu_registers);

    i8259_send_eoi(interrupt_registers->interrupt_number);
}
void interrupt_exception_handler(general_registers_t registers){
    kprintf("exception caught\n");
}

void irq_install_handler(int irq, void (*handler)(general_registers_t*)){
    irqs[irq] = handler;
}
