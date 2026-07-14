#include "drivers/keyboard.h"
#include "drivers/vga.h"
#include "gdt.h" #include "multiboot.h"
#include "pci.h"
#include "pit.h"
#include "scheduler.h"
#include "tcb.h"
#include "io.h"
#include "acpi.h"
#include "interrupts.h"
#include "drivers/ps2.h"
#include "drivers/keyboard.h"
#include "malloc.h"
#include "apic.h"
#include "idt.h"
#include "string.h"
#include "usb.h"
#include "tty.h"
#include <stddef.h>

void test_malloc(){
    kprintf("Testing malloc\n");

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
void kernel_thread_start1();
void kernel_thread_start2();
void kernel_main(multiboot1_header_t* multiboot_header){
    kheap_init();
    vga_init(&multiboot_header->framebuffer);
    const char* str = "hello world";
    tty_init(get_current_tty());

    kprintf("Starting kernel\n");
    uint32_t flags = multiboot_header->flags;
    kprintf("Multiboot at %p with flags %b\n", (size_t)multiboot_header, flags);

    if(flags & (1 << MULTIBOOT_BOOT_LOADER_NAME_BIT)){
        const char* name = (const char*)multiboot_header->boot_loader_name;
        kprintf("Got bootloader name \"%s\" addr %p offset %d\n", name, name, offsetof(multiboot1_header_t, boot_loader_name));
    }

    //locate_acpi_tables();
    setup_gdt();
    setup_idt();
    apic_init();
    pit_init();
    usb_init();
    ps2_init();
    keyboard_init();

    kprintf("Done initializing kernel\n");
    enable_interrupts();
    
    tcb_t* kernel_thread_1 = create_tcb(kernel_thread_start1);
    add_task(kernel_thread_1);
    tcb_t* kernel_thread_2 = create_tcb(kernel_thread_start1);
    add_task(kernel_thread_2);
    khalt();
}

void kernel_thread_start1(){
    while(true){
        kprintf("Kernel Thread 1\n");
        khalt();
    }
}
void kernel_thread_start2(){
    while(true){
        kprintf("Kernel Thread 2\n");
        khalt();
    }
}
