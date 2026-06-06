#include "teletype.h"
#include "video.h"

extern void kend();

void kmain(){
    PrintString("Kernel main called" ENDL);
    kend();
}
