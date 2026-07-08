#ifndef IDT_H
#define IDT_H
#include "gdt.h"
#include "segment.h"

// All being subtracted by 40 since we are accessing via fields field in idt descriptor. compiler can optimize
#define IDG_P_FLAG_BIT 7
#define IDG_P_FLAG_BIT_WIDTH 1

#define IDG_DPL_BIT 5
#define IDG_DPL_BIT_WIDTH 2

#define IDG_GATE_TYPE_BIT 0
#define IDG_GATE_TYPE_BIT_WIDTH 4

enum itr_gate_type_e_{
    IDG_TASK=0x5,
    IDG_16_BIT_INTERRUPT_GATE=0x6,
    IDG_16_BIT_TRAP_GATE=0x7,
    IDG_32_BIT_INTERRUPT_GATE=0xE,
    IDG_32_BIT_TRAP_GATE=0xF
};

typedef struct idt_entry_t{
    uint16_t offset_low;

    // Selector with fields theat points to a valid segment in gdt
    segment_selector_t segment_selector;

    uint8_t reserved;
    uint8_t fields;
    uint16_t offset_high;
}__attribute__((packed)) idt_entry_t;

idt_entry_t create_idt_entry(uint32_t offset, segment_selector_t segment_selector, bool present, uint8_t dpl, uint8_t gate_type);
void init_idt();

#endif
