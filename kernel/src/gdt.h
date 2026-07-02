#ifndef GDT_H
#define GDT_H
#include <stddef.h>

struct gdt_t{
    size_t offset;
    size_t size;
};

extern void load_gdt(struct gdt_t* gdt, size_t size);

void setup_gdt();

#endif
