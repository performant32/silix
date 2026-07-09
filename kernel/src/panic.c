#include "panic.h"
#include "interrupts.h"
#include "io.h"

extern void khalt();

void kpanic(){
    kprintf("\nKERNEL PANIC\n"); 
    disable_interrupts();
    khalt();
}
