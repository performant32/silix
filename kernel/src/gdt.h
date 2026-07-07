#ifndef GDT_H
#define GDT_H

#include "segment.h"
#include <stddef.h>
#include <stdint.h>

typedef struct gdt_descriptor_t{
    // The size of the table in bytes - 1
    uint16_t size;
    size_t offset;
}__attribute__((packed)) gdt_descriptor_t;

//extern segment_descriptor_t gdt_table[2];

/*
enum gdt_access_bits_e{
    GDT_PRESENT=(1 << 7),
    GDT_DPL= 0b01100000,
    GDT_S=1 << 4,
    GDT_E=1 << 3,
    GDT_DC=(1 << 2),
    GDT_RW=(1 << 1),
    GDT_A = 1<<0
};
*/


extern void load_gdt(struct gdt_descriptor_t* gdt);
extern void load_idt(struct gdt_descriptor_t* gdt);

void setup_gdt();
void setup_idt();
extern void reload_segment_registers();
#endif
