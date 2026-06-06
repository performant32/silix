#include "teletype.h"
//#include "bios_reader.h"

#define ENDL "\12\15"
extern void print();
void __cdecl start(){
    PrintString("Loading Kernel" ENDL);
    int x = 0;//ReadDisk({0,0,0});
    if(x == 0)
        PrintString("Was false" ENDL);
    else
        PrintString("Was true" ENDL);
}
