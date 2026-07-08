#include "idt.h"
#include "io.h"
#include "interrupts.h"
#include "bit_fields.h"

idt_entry_t idt_entries[256] = {0};

idt_entry_t create_idt_entry(uint32_t offset, segment_selector_t segment_selector, bool present, uint8_t dpl, uint8_t gate_type){
    idt_entry_t idt_entry =(idt_entry_t){0};
    idt_entry.offset_low = offset & 0xFFFF;
    idt_entry.offset_high = (offset >> 16) & 0xFFFF;
    idt_entry.fields = BITS((int)present, IDG_P_FLAG_BIT, IDG_P_FLAG_BIT_WIDTH);
    idt_entry.fields |= BITS(dpl, IDG_DPL_BIT, IDG_DPL_BIT_WIDTH);
    idt_entry.fields |= BITS(gate_type, IDG_GATE_TYPE_BIT, IDG_GATE_TYPE_BIT_WIDTH);
    idt_entry.segment_selector = segment_selector;
    return idt_entry;
}

void setup_idt(){
    kprintf("Setting up idt\n");

    uintptr_t offset = (uintptr_t)isr_wrapper;
    segment_selector_t segment = create_segment_selector(
        1,
        SEGMENT_USE_GDT,
        0
    );
    kprintf("Segment is %d\n", segment);
    for(size_t i = 0; i < 32; i++){
        idt_entry_t entry = create_idt_entry(offset, segment, true, 0, IDG_32_BIT_INTERRUPT_GATE);
        idt_entries[i] = entry;
    }
    for(size_t i = 32; i < 256; i++){
        idt_entry_t entry = create_idt_entry(offset, segment, true, 0, IDG_32_BIT_INTERRUPT_GATE);
        idt_entries[i] = entry;
    }

    gdt_descriptor_t idt_descriptor = (gdt_descriptor_t){0};
    idt_descriptor.size = (sizeof(idt_entry_t) * 256) - 1;
    idt_descriptor.offset = (size_t)idt_entries;

    kprintf("Loading IDT %p with size %x, isr at %p\n", idt_descriptor.offset, idt_descriptor.size, (size_t)isr_wrapper);
    load_idt(&idt_descriptor);
}
