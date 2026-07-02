#ifndef GDT_H
#define GDT_H
#include <stddef.h>
#include <stdint.h>

typedef struct gdt_descriptor_t{
    // The size of the table in bytes - 1
    uint16_t size;
    size_t offset;
} gdt_descriptor_t;

typedef struct gdt_entry_t{
    uint8_t data[8];
} gdt_entry_t;

extern gdt_entry_t gdt_table[2];

enum gdt_access_bits_e{
    GDT_PRESENT=(1 << 7),
    GDT_DPL= 0b01100000,
    GDT_S=1 << 4,
    GDT_E=1 << 3,
    GDT_DC=(1 << 2),
    GDT_RW=(1 << 1),
    GDT_A = 1<<0
};

extern void load_gdt(struct gdt_descriptor_t* gdt);

void setup_gdt();

#endif
