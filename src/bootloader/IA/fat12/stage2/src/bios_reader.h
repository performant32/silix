#ifndef BIOS_READER_H
#define BIOS_READER_H
#include "ints.h"

typedef struct CHS{
    uint8_t m_Cylinder;
    uint8_t m_Head;
    uint8_t m_Sector;
} CHS;

CHS LBAToCHS(uint16_t lba){
    return {0,0,0};
}
#endif
