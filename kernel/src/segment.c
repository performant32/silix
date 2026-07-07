#include "segment.h"
#include "bit_fields.h"

segment_selector_t create_segment_selector(uint16_t index, uint8_t table_index, uint8_t rpl){
    return BITS(index, SEGMENT_INDEX_BIT, SEGMENT_INDEX_BIT_WIDTH) | BITS(table_index, SEGMENT_TI_BIT, SEGMENT_TI_BIT_WIDTH) | BITS(rpl, SEGMENT_RPL_BIT, SEGMENT_RPL_BIT_WIDTH);
}

segment_descriptor_t create_descriptor(uint32_t base, uint32_t limit, uint8_t flags, uint8_t access_byte){
    segment_descriptor_t descriptor;
    descriptor.limit_lo = limit & 0xFFFF;
    descriptor.flags_n_limit_hi2 = (limit >> 16) & 0xF;

    descriptor.access_byte = access_byte;
    descriptor.flags_n_limit_hi2 |= BITS(flags, 4, 4);

    descriptor.base_lo = base & 0xFFFF;
    descriptor.base_hi1 = (base >> 16) & 0xFF;
    descriptor.base_hi2 = (base >> 24) & 0xFF;

    return descriptor;
}
uint16_t segment_get_index(uint16_t segment){
    return GET_BITS(segment, SEGMENT_INDEX_BIT, SEGMENT_INDEX_BIT_WIDTH);
}
uint16_t segment_get_ti(uint16_t segment){
    return GET_BITS(segment, SEGMENT_TI_BIT, SEGMENT_TI_BIT_WIDTH);
}
uint16_t segment_get_rpl(uint16_t segment){
    return GET_BITS(segment, SEGMENT_RPL_BIT, SEGMENT_RPL_BIT_WIDTH);
}
