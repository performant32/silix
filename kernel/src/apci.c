#include "apci.h"

#include <stddef.h>

#include "io.h"
#include "string.h"
#include "panic.h"

const char* rsdp_checksum = "RSD PTR ";

void locate_apci_tables(){
    kprintf("Locating ACPI Tables\n");

    char* firstSearch = (char*)(0x40E);
    char* endSearch = (char*)(1024 * 1000);

    //TODO: check other possible locations aswell
    while(firstSearch < endSearch){
        if(strncmp(firstSearch, rsdp_checksum, 8) == 0){
            goto located;
        }
        firstSearch++;
    }
    firstSearch = (char*)0xE0000;
    endSearch = (char*)0xFFFFF;
    while(firstSearch < endSearch){
        if(strncmp(firstSearch, rsdp_checksum, 8) == 0){
            goto located;
        }
        firstSearch++;
    }
    kprintf("Failed to locate rsdp\n");
    kpanic();
located:

    struct rsdp_t* rsdp = (struct rsdp_t*)firstSearch;

    uint8_t checksum = 0;
    for(int i = 0; i < sizeof(struct rsdp_t); i++){
        checksum+=((char*)(rsdp))[i];
    }
    if(checksum != 0){
        kprintf("Failed to validate apci, got %u\n", checksum);
        kpanic();
    }
    kprintf("Located acpi tables at %p.\n", rsdp_checksum);
    kprintf("OEM: ");
    //TODO: implement %.*s
    for(int i = 0; i < 6; i++){
        kprintf("%c", (char)rsdp->oemid[i]);
    }
    kprintf("\n");
    
}
