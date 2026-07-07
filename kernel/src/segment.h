#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>

#define SEGMENT_RPL_BIT 0
#define SEGMENT_RPL_BIT_WIDTH 2

#define SEGMENT_TI_BIT 2
#define SEGMENT_TI_BIT_WIDTH 1

#define SEGMENT_INDEX_BIT 3
#define SEGMENT_INDEX_BIT_WIDTH 12

typedef uint16_t segment_selector_t;

enum segment_table_descriptor_e{
    SEGMENT_USE_GDT=0,
    SEGMENT_USE_LDT=1
};

// 0 bc flags_n_limit_hi own field
#define SEGMENT_ENTRY_LIMIT_HI 0
#define SEGMENT_ENTRY_LIMIT_HI_WIDTH 4

// Present bit refers to a valid entry
#define SEGMENT_ACCESS_P_BIT 7
#define SEGMENT_ACCESS_P_BIT_WIDTH 1

// Descriptor privilege legel
#define SEGMENT_ACCESS_DPL_BIT 5
#define SEGMENT_ACCESS_DPL_BIT_WIDTH 2

// Descriptor type bit. if clean defines system segment(task segment or something), if 1 defiens code or data segment
#define SEGMENT_ACCESS_S_BIT 4
#define SEGMENT_ACCESS_S_BIT_WIDTH 1

// Executable bit. if clear defines a data segment. if 1 defines code segment
#define SEGMENT_ACCESS_E_BIT 3
#define SEGMENT_ACCESS_E_BIT_WIDTH 1

// Direct bit/ Conforming bit
// for data selectors if 0, segment grows up. if 1 grows down. offset has to be greatar than limit
// for code selectors. if clear, segment can only be executed from ring in dpl
// if can be executed from equal or lower privilege levels. dpl represents highest privilege level that can access
#define SEGMENT_ACCESS_DC_BIT 2
#define SEGMENT_ACCESS_DC_BIT_WIDTH 1

// Read/writable bit
#define SEGMENT_ACCESS_RW_BIT 1
#define SEGMENT_ACCESS_RW_BIT_WIDTH 1

// Accessed bit. set when cpu is accessed unless 1 in advance
#define SEGMENT_ACCESS_A_BIT 0
#define SEGMENT_ACCESS_A_BIT_WIDTH 1

enum descriptor_flags_e{
    // indicates the size the limit value is scaled by. if 0 the limit is in 1 byte blocks, if 1 the limit is in 4 KiB blocks
    DESCRIPTOR_GRANULARITY_BIT=3,
    // if clear defiens a 16 bit protected mode segment. if 1 defines a 32 bit protected mode segment. gdt can have both
    DESCRIPTOR_SIZE_BIT=2,
    // long mode code flag. if 1 descriptor defines 64 bit code segment. when set db should always be clear. for other types of segments. should be clear
    DESCRIPTOR_LONG_MODE_BIT=1,
};
typedef struct segment_descriptor_t{
    // where segment begins
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t base_hi1;
    uint8_t access_byte;
    uint8_t flags_n_limit_hi2;
    uint8_t base_hi2;
}__attribute__((packed)) segment_descriptor_t;

segment_descriptor_t create_descriptor(uint32_t base, uint32_t limit, uint8_t flags, uint8_t access_byte);
segment_selector_t create_segment_selector(uint16_t index, uint8_t table_index, uint8_t rpl);
uint16_t segment_get_index(uint16_t segment);
uint16_t segment_get_ti(uint16_t segment);
uint16_t segment_get_rpl(uint16_t segment);

#endif
