#include "apic.h"
#include "acpi.h"
#include "panic.h"
#include "io.h"

#include "i8259.h"

void apic_init(){
    // Larp apic and just use 8259
    i8259_init();

    /*
    kprintf("Initializing APIC\n");
    fadt_t* fadt = locate_acpi_table("FACP");
    if(!fadt){
        kprintf("Failed to locate fadt\n");
        kpanic();
    }
    // TODO: check if supports APIC
    madt_t* madt = locate_acpi_table("APIC");
    if(!madt){
        kprintf("Failed to locate madt\n");
        kpanic();
    }

    // TODO: verifying madt checksum
    madt_entry_t* current = (madt_entry_t*)((size_t)madt + sizeof(madt_t));
    // while((size_t)current < (size_t)madt + madt->header.length){
    //     uint8_t type;
    //     switch(type){
    //
    //     }
    // }

    kprintf("Initialized APIC\n");
    */
}
