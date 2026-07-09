#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

enum multiboot1_flags{
    MULTIBOOT_BOOT_DEVICE_FLAG_BIT=1,
    MULTIBOOT_BOOT_LOADER_NAME_BIT=9
};

typedef struct multiboot1_header_t{
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mod_count;
    uint32_t mods_addr;
    uint8_t syms[16];
    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name;
}__attribute__((packed)) multiboot1_header_t;

#endif
