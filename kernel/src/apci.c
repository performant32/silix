#include "apci.h"

#include <stddef.h>

#include "io.h"
#include "string.h"
#include "panic.h"

const char* rsdp_checksum = "RSD PTR";

void locate_apci_tables(){
    kprintf("Locating ACPI Tables\n");

    char* firstSearch = (char*)(0x40E);
    char* endSearch = (char*)(1024 * 1000);
    bool located = false;

    //TODO: check other possible locations aswell
    while(firstSearch < endSearch){
        if(strncmp(firstSearch, rsdp_checksum, strlen(rsdp_checksum)) == 0){
            located = true;
            kprintf("Located acpi tables at %p.\n", rsdp_checksum);
            break;
        }
        firstSearch++;
    }
    if(!located){
        kprintf("Failed to locate apci tables, could not find signature %s\n", rsdp_checksum);
        kpanic();
        return;
    }

    struct rsdp_t* rsdp = (struct rsdp_t*)firstSearch;

    uint8_t checksum = 0;
    for(int i = 0; i < sizeof(struct rsdp_t); i++){
        checksum+=((char*)(rsdp))[i];
    }
    if(checksum != 0){
        kprintf("Failed to validate apci, got %u\n", checksum);
        kpanic();
    }
}
