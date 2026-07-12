#ifndef VGA_H
#define VGA_H
#include "multiboot.h"

enum vga_framebuffer_type_e{
    VGA_FB_USE_INDEXED=0,
    VGA_FB_USE_RGB=1,
    VGA_FB_USE_EGA=2,
};

typedef struct vga_info_t{
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint32_t bpp;
}vga_info_t;

uint8_t* vga_get_framebuffer_addr();
vga_info_t* get_vga_info();

void vga_init(framebuffer_info_t* info);
void vga_clear_screen(uint32_t color);

#endif
