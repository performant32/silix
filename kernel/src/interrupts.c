#include "interrupts.h"
#include "io.h"
#include "i8259.h"
#include "drivers/keyboard.h"

void interrupt_handler(registers_t registers){
    kprintf("Interrupt received\n");

    uint16_t isr = i8259_get_isr();
    kprintf("Register %b beign serviced\n", isr);
    // TODO: Find out what kind of interrupt this was and if spurious
    // Also handle cases where interrupts happen inside interrupts and whatever
    if(isr == 1){
        keyboard_interrupt();
    }

    i8259_send_eoi(1);
    kprintf("Interrupt Ended\n");
}
void interrupt_exception_handler(registers_t registers){
    kprintf("exception caught\n");
}
