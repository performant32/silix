#include "gdt.h"
#include "io.h"

gdt_entry_t gdt_table[2] = (gdt_entry_t[2]){
    {0}
};

void setup_gdt(){
    kprintf("Setting up gdt\n");

    struct gdt_descriptor_t gdt_descriptor = (struct gdt_descriptor_t){0, 0};
    gdt_descriptor.offset = (typeof(gdt_descriptor.offset))gdt_table;
    gdt_descriptor.size = sizeof(gdt_entry_t) - 1;

    load_gdt(&gdt_descriptor);
    kprintf("Initialized gdt\n");
}
