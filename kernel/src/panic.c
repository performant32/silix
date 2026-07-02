#include "panic.h"
#include "io.h"

extern void khalt();

void kpanic(){
    kprintf("\nKERNEL PANIC\n"); 
    khalt();
}
