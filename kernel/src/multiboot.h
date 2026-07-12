#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

enum multiboot1_flags{
    MULTIBOOT_BOOT_DEVICE_FLAG_BIT=1,
    MULTIBOOT_BOOT_LOADER_NAME_BIT=9
};

typedef struct vbe_info_t{
    uint32_t control_info;
    uint32_t mode_info;
    uint16_t mode;
    uint16_t interface_seg;
    uint16_t interface_off;
    uint16_t interface_len;
}__attribute__((packed)) vbe_info_t;

typedef struct framebuffer_info_t{
    uint64_t address;
    uint32_t pitch;
    uint32_t width;
    uint32_t height;
    uint8_t bpp; // bits per pixel
    uint8_t type;
    union{
        struct{
            uint32_t palette_addr;
            uint32_t palette_num_colors;
        }__attribute__((packed))indexed;
        struct{
            uint8_t red_field_position;
            uint8_t red_mask_size;
            uint8_t green_field_position;
            uint8_t green_mask_size;
            uint8_t blue_field_position;
            uint8_t blue_mask_size;
        }__attribute__((packed)) color_type;
    };

}__attribute__((packed)) framebuffer_info_t;
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
    uint32_t apm_table;
    vbe_info_t vbe;
    framebuffer_info_t framebuffer;
}__attribute__((packed)) multiboot1_header_t;

#endif
