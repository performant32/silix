#include "mmap.h"
#include "io.h"
#include "multiboot.h"
#include "panic.h"
#include "malloc.h"
#include <stddef.h>

static memory_map_t* s_acpi_memory_regions=NULL;
static size_t s_acpi_memory_region_count=0;

void initialize_mmap(multiboot1_header_t* header){
    kprintf("Initializing memory map from multiboot\n");
    if(!multiboot1_has_mmap(header)){
        kprintf("Failed to initialize kernel memory map, bootloader failed to supply startup information\n");
        kpanic();
    } 

    // for now we are just gonna hog up the kernel heap

    size_t at = header->mmap_addr;
    while(at < header->mmap_addr + header->mmap_length){
        multiboot1_mmap_full_t* pair = (multiboot1_mmap_full_t*)at;
        multiboot1_mmap_t* mmap = &pair->mmap;
        switch(mmap->type){
        case MULTIBOOT1_MMAP_USABLE_ACPI:{
            kprintf("Found area of memory for acpi at %p\n", mmap->base_addr);
            s_acpi_memory_regions = krealloc(s_acpi_memory_regions, sizeof(memory_map_t) * s_acpi_memory_region_count+1);
            s_acpi_memory_regions[s_acpi_memory_region_count++]=(memory_map_t){
                (void*)mmap->base_addr,
                mmap->length
            };
        }break;

        default:{
            kprintf("Warning! Unsupported memory region %d\n", mmap->type);
        }break;
        }
        at+=pair->size+sizeof(uint32_t);
    }
    // Hardcode since we are only using multiboot1 which apparently isnt great at finding
    //skrealloc(s_acpi_memory_regions, s_acpi_memory_region_count);
}
memory_map_t** get_acpi_memory_regions(){
    return &s_acpi_memory_regions;
}
size_t get_acpi_memory_regions_count(){
    return s_acpi_memory_region_count;
}
