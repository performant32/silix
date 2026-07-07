#include "interrupts.h"
#include "io.h"

void interrupt_handler(){
    kprintf("Interrupt received");
}
