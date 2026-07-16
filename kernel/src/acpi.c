#include "acpi.h"

#include <stddef.h>

#include "gdt.h"
#include "io.h"
#include "string.h"
#include "panic.h"
#include "mmap.h"

const char rsdp_checksum[8] = "RSD PTR ";
const char rsdt_signature[4] = "RSDT";
rsdp_t* rsdp = NULL;
rsdt_t* rsdt = NULL;

void locate_acpi_tables(){
    kprintf("Locating ACPI Tables\n");
    memory_map_t** acpi_memory = get_acpi_memory_regions();
    size_t acpi_region_count = get_acpi_memory_regions_count();
    if(acpi_region_count == 0){
        kprintf("Failed to find any acpi regions\n");
        kpanic();
    }

    char* first_search = NULL;
    for(size_t i = 0; i < acpi_region_count; i++){
        first_search = (char*)acpi_memory[i]->data;
        char* end_search = first_search + acpi_memory[i]->size;

        const unsigned acpi_byte_boundary = 16;
        while(first_search < end_search){
            if(strncmp(first_search, rsdp_checksum, 8) == 0 && (size_t)first_search % acpi_byte_boundary == 0){
                goto located;
            }
            first_search++;
        }
    }
    kprintf("Failed to locate rsdp\n");
    kpanic();
located:
    rsdp = (struct rsdp_t*)first_search;

    uint8_t checksum = 0;
    for(int i = 0; i < sizeof(struct rsdp_t); i++){
        checksum+=((char*)rsdp)[i];
    }
    if(checksum != 0){
        kprintf("Failed to validate apci, got %u, revision %u\n", checksum, rsdp->revision);
        kpanic();
    }
    kprintf("Located acpi tables at %p with revision %d\n", rsdp_checksum, rsdp->revision);
    if(rsdp->revision > 1){
        struct xsdp_t* xsdp = (struct xsdp_t*)rsdp;
        checksum = 0;
        for(int i = 0; i < sizeof(struct xsdp_t); i++){
            checksum+=((char*)(xsdp))[i];
        }
        if(checksum != 0){
            kprintf("Failed to validate apci with revision %d, got %u %d\n", checksum, xsdp->rsdp.revision);
            kpanic();
        }
        kprintf("Using xsdp\n");
    }
    kprintf("OEM: %.*s\n", 6, (char*)rsdp->oemid);

    sdt_header_t* sdt_header = (sdt_header_t*)(rsdp->rsdt_address);
    if(!rsdt_verify_checksum(sdt_header)){
        kprintf("sdt header has invalid checksum\n");
        kpanic();
    }
    kprintf("Located sdt header at %p with signature %.*s\n", sdt_header, 4, sdt_header->signature);
    rsdt = (rsdt_t*)sdt_header;
    void* facp = locate_acpi_table("FACP");
    if(!facp){
        kprintf("Failed to locate facp\n");
        kpanic();
    }
}
void* locate_acpi_table(char signature[4]){
    int entries = (rsdt->header.length - sizeof(rsdt->header)) / 4;
    for(int i = 0; i < entries; i++){
        sdt_header_t* entry_header = (sdt_header_t*)rsdt->entries[i];
        if(!strncmp(entry_header->signature, signature, 4)){
            return entry_header;
        }
    }
    return NULL;
}

bool rsdt_verify_checksum(sdt_header_t* header){
    uint8_t sum = 0;
    for(size_t i={}; i < header->length; i++){
        sum+=((uint8_t*)header)[i];
    }
    return sum == 0;
}

rsdp_t* rsdp_get(){
    return rsdp;
}
