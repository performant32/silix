#include "interrupts.h"
#include "io.h"
#include "i8259.h"
#include "drivers/keyboard.h"
#include "registers.h"

static void(*irqs[16])(registers_t*)={0};

void interrupt_handler(interrupt_registers_t interrupt_registers){
    uint8_t irq_line = interrupt_registers.interrupt_number;
    if(irq_line == 255){
        //return;
    }
    kprintf("Interrupt received line %d\n", irq_line);
    if(irq_line > 16){
        kprintf("Unsupported irq %d\n", irq_line);
        return;
    }
    // TODO: Find out what kind of interrupt this was and if spurious
    // Also handle cases where interrupts happen inside interrupts and whatever

    // if(isr == 1){
    //     keyboard_interrupt();
    // }
    void (*handler)(registers_t* registers) = irqs[irq_line];
    if(!handler){
        kprintf("Warning. Unsupported interrupt %u\n", irq_line);
        i8259_send_eoi(irq_line);
        return;
    }
    handler(&interrupt_registers.cpu_registers);

    i8259_send_eoi(interrupt_registers.interrupt_number);
    kprintf("Interrupt Ended\n");
}
void interrupt_exception_handler(registers_t registers){
    kprintf("exception caught\n");
}

void irq_install_handler(int irq_line, void (*handler)(registers_t*)){
    irqs[irq_line] = handler;
}
