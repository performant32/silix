#include "gdt.h"
#include "interrupts.h"
#include "privilege.h"
#include "bit_fields.h"
#include "io.h"
#include "segment.h"

segment_descriptor_t gdt_table[3] = (segment_descriptor_t[3]){
    {0}
};

void setup_gdt(){
    kprintf("Setting up gdt\n");

    struct gdt_descriptor_t gdt_descriptor = (struct gdt_descriptor_t){0, 0};
    gdt_descriptor.offset = (size_t)gdt_table;
    gdt_descriptor.size = (sizeof(segment_descriptor_t) * 3) - 1;

    uint32_t base=0;
    uint32_t limit=-1;
    kprintf("Base %u limit %u sizeof segment descriptor in bytes %d\n", base, limit, sizeof(segment_descriptor_t));
    uint8_t flags=BITS(1, DESCRIPTOR_GRANULARITY_BIT, 1) | BITS(0, DESCRIPTOR_LONG_MODE_BIT, 1) | BITS(1, DESCRIPTOR_SIZE_BIT, 1);
    uint8_t access_byte=0;

    gdt_table[0] = create_descriptor(0, 0, 0, 0);

    kprintf("Descriptor flags 0x%x\n", flags);
    // Code segment
    access_byte= BITS(1, SEGMENT_ACCESS_P_BIT, SEGMENT_ACCESS_P_BIT_WIDTH);
    access_byte|=BITS(0, SEGMENT_ACCESS_DPL_BIT, SEGMENT_ACCESS_DPL_BIT_WIDTH);
    access_byte|=BITS(1, SEGMENT_ACCESS_S_BIT, SEGMENT_ACCESS_S_BIT_WIDTH);
    access_byte|=BITS(1, SEGMENT_ACCESS_E_BIT, SEGMENT_ACCESS_E_BIT_WIDTH);
    access_byte|=BITS(0, SEGMENT_ACCESS_DC_BIT, SEGMENT_ACCESS_DC_BIT_WIDTH);
    access_byte|=BITS(1, SEGMENT_ACCESS_RW_BIT, SEGMENT_ACCESS_RW_BIT_WIDTH);
    access_byte|=BITS(1, SEGMENT_ACCESS_A_BIT, SEGMENT_ACCESS_A_BIT_WIDTH);
    kprintf("Code segment access byte %x\n", access_byte);

    gdt_table[1] = create_descriptor(base, limit, flags, access_byte);

    // Data segment
    access_byte= BITS(1, SEGMENT_ACCESS_P_BIT, SEGMENT_ACCESS_P_BIT_WIDTH);
    access_byte|=BITS(0, SEGMENT_ACCESS_DPL_BIT, SEGMENT_ACCESS_DPL_BIT_WIDTH);
    access_byte|=BITS(1, SEGMENT_ACCESS_S_BIT, SEGMENT_ACCESS_S_BIT_WIDTH);
    access_byte|=BITS(0, SEGMENT_ACCESS_E_BIT, SEGMENT_ACCESS_E_BIT_WIDTH);
    access_byte|=BITS(0, SEGMENT_ACCESS_DC_BIT, SEGMENT_ACCESS_DC_BIT_WIDTH);
    access_byte|=BITS(1, SEGMENT_ACCESS_RW_BIT, SEGMENT_ACCESS_RW_BIT_WIDTH);
    access_byte|=BITS(1, SEGMENT_ACCESS_A_BIT, SEGMENT_ACCESS_A_BIT_WIDTH);
    kprintf("Data segment access byte %x\n", access_byte);

    gdt_table[2] = create_descriptor(base, limit, flags, access_byte);
    kprintf("GDT Descriptor contains %x %x\n", gdt_descriptor.offset, gdt_descriptor.size);
    kprintf("GDT descriptor at is %p, table is %p\n", &gdt_descriptor, gdt_table);

    disable_interrupts();
    load_gdt(&gdt_descriptor);
    kprintf("Initialized gdt at %p\n", gdt_table);
}
