#include "interrupts.h"
#include "io.h"
#include "i8259.h"
#include "drivers/keyboard.h"

void interrupt_handler(){
    kprintf("Interrupt received\n");
    keyboard_interrupt();

    i8259_send_eoi(1);
    kprintf("Interrupt Ended\n");
}
