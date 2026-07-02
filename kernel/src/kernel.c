#include "gdt.h"
#include "video.h"
#include "io.h"
#include "apci.h"

void kernelMain(void){
    vga_clear_screen();
    kprintf("Starting kernel\n");
    kprintf("Decimal %d, unsigned %d, Octal: %o, Hex: %x\n", -123456789, 123456789, 8 * 8, 0b10101111);

    unsigned int i = 0;
    unsigned int j = 0;
    //locate_apci_tables();
    setup_gdt();

    return;
}

