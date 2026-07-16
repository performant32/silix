#ifndef MMAP_H
#define MMAP_H

#include <stddef.h>

// Used to store some memory mapping with the kernel
// Mostly just the ACPI tables so far

#include "multiboot.h"

typedef struct memory_map_t{
    void* data;
    size_t size;
}memory_map_t;

void initialize_mmap(multiboot1_header_t* header);

// Returns the memory area for ACPI. Just incase more than 1 acpi region
memory_map_t** get_acpi_memory_regions();
size_t get_acpi_memory_regions_count();

#endif
