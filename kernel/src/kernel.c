#include "drivers/keyboard.h"
#include "gdt.h"
#include "pci.h"
#include "video.h"
#include "io.h"
#include "acpi.h"
#include "interrupts.h"
#include "drivers/keyboard.h"
#include "malloc.h"
#include "apic.h"
#include "idt.h"
#include "string.h"
#include "usb.h"

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
void kernel_main(void){
    vga_clear_screen();
    kprintf("Starting kernel\n");
    kprintf("Decimal %d, unsigned %u, Octal: %o, Hex: %x\n", -1234567, 123456, 8 * 8, 0b10101111);

    //test_malloc();
    locate_acpi_tables();
    setup_gdt();
    setup_idt();
    apic_init();
    enable_interrupts();
    usb_init();
    interrupt_test();
    kprintf("Done initializing kernel\n");
    keyboard_init();
    //pcie_init();
    khalt();
}

