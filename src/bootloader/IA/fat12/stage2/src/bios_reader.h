#ifndef BIOS_READER_H
#define BIOS_READER_H
#include "ints.h"

typedef struct CHS{
    uint8_t m_Cylinder;
    uint8_t m_Head;
    uint8_t m_Sector;
} CHS;

CHS __cdecl LBAToCHS(uint16_t lba){
    CHS chs = {0,56,0};
    return chs;
}

extern int __cdecl ReadDisk(CHS chs);

#endif
