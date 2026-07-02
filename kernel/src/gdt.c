#include "gdt.h"
#include "io.h"

void setup_gdt(){
    kprintf("Setting up gdt\n");

    struct gdt_t gdt = (struct gdt_t){0, 0};
    load_gdt(&gdt, sizeof(gdt));
}
