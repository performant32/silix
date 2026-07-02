#include "gdt.h"
#include "video.h"
#include "io.h"
#include "apci.h"
#include "malloc.h"
#include <stdio.h>
#include <string.h>

void test_malloc(){
    kprintf("Testing malloc\n");
    kheap_init();

    int size = 100;
    char* data1 = (char*)kmalloc(size);
    kprintf("Allocated %d bytes %p\n", size, data1);
    memset(data1, '5', size);

    kprintf("Data1: %p\n", data1);
    size = 200;
    char* data2 = (char*)kmalloc(size);
    kprintf("Allocated %d bytes %p\n", size, data2);
    memset(data2, '6', size);
    kprintf("Data2: %p\n", data2);

    kprintf("Freeing data1 %p\n", data1);
    kfree(data1);
    data1 = NULL;

    size = 5000;
    char* data3 = (char*)kmalloc(size);
    kprintf("Allocated %d bytes %p\n", size, data3);
    memset(data3, '1', size);

    size = 100;
    data1 = kmalloc(size);
    kprintf("Allocated %d bytes %p\n", size, data1);

    kprintf("Done testing Malloc\n");
}
void kernelMain(void){
    vga_clear_screen();
    kprintf("Starting kernel\n");
    kprintf("Decimal %d, unsigned %u, Octal: %o, Hex: %x\n", -123456, 123456, 8 * 8, 0b10101111);

    test_malloc();
    locate_apci_tables();
    setup_gdt();

    return;
}

