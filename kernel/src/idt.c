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
    segment_selector_t segment_selector = create_segment_selector(
        1,
        SEGMENT_USE_GDT,
        0
    );
    //TODO: some are traps
    for(size_t i = 32; i < 256; i++){
        idt_entries[i] = create_idt_entry((uintptr_t)spurious_interrupt, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    }

    for(size_t i = 0; i < 32; i++){
        idt_entries[i] = create_idt_entry((uintptr_t)interrupt_exception, segment_selector, true, 0, IDG_32_BIT_TRAP_GATE);
    }

    idt_entries[IRQ_BEGIN + 0] =  create_idt_entry((size_t)irq0, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 1] =  create_idt_entry((size_t)irq1, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 2] =  create_idt_entry((size_t)irq2, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 3] =  create_idt_entry((size_t)irq3, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 4] =  create_idt_entry((size_t)irq4, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 5] =  create_idt_entry((size_t)irq5, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 6] =  create_idt_entry((size_t)irq6, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 7] =  create_idt_entry((size_t)irq7, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 8] =  create_idt_entry((size_t)irq8, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 9] =  create_idt_entry((size_t)irq9, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 10] = create_idt_entry((size_t)irq10, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 11] = create_idt_entry((size_t)irq11, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 12] = create_idt_entry((size_t)irq12, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 13] = create_idt_entry((size_t)irq13, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 14] = create_idt_entry((size_t)irq14, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);
    idt_entries[IRQ_BEGIN + 15] = create_idt_entry((size_t)irq15, segment_selector, true, 0, IDG_32_BIT_INTERRUPT_GATE);

    gdt_descriptor_t idt_descriptor = (gdt_descriptor_t){0};
    idt_descriptor.size = (sizeof(idt_entry_t) * 256) - 1;
    idt_descriptor.offset = (size_t)idt_entries;

    idt_entry_t entry_test = idt_entries[IRQ_BEGIN + 0];
    kprintf("Entry %x\n", (entry_test.offset_high << 16) | entry_test.offset_low);

    kprintf("Spurious location %p, irq0%p\n", spurious_interrupt, irq0);

    kprintf("Loading IDT %p with size %x\n", idt_descriptor.offset, idt_descriptor.size);
    load_idt(&idt_descriptor);
}
