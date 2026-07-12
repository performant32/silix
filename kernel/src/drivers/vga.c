#include "vga.h"

#include "io.h"

static vga_info_t vga_info=(vga_info_t){0};
static uint8_t* framebuffer_addr; 
static int column = 0;
static int row = 0;

uint8_t* vga_get_framebuffer_addr(){
    return framebuffer_addr;
}
vga_info_t* get_vga_info(){
    return &vga_info;
}
void draw_pixel(int x, int y, uint32_t pixel){
    framebuffer_addr[y + x] = pixel;
}
void vga_init(framebuffer_info_t* info){
    vga_info.width = info->width;
    vga_info.height = info->height;
    vga_info.pitch = info->pitch;
    vga_info.bpp = info->bpp;

    framebuffer_addr = (uint8_t*)info->address;
    switch (info->type) {
        case VGA_FB_USE_INDEXED:
            break;
        case VGA_FB_USE_RGB:
            break;
        case VGA_FB_USE_EGA:
            break;
    }
    // for(int x = 0; x < info->width; x++){
    //     for(int y = 0; y < info->width; y++){
    //         *((uint32_t*)(framebuffer_addr + y * vga_info.pitch + x * 4)) = 255;
    //     }
    // }
    //kprintf("VGA Init\n")
    vga_clear_screen(0xFFFFFFFF);
}

void vga_clear_screen(uint32_t color){
    for(int x = 0; x < vga_info.width; x++){
        for(int y = 0; y < vga_info.width; y++){
            uint32_t c = 0xFFFFFFFF;
            if((x + y) % 2 == 0){
                c = 0xFF00FF00;
            }
            *((uint32_t*)(framebuffer_addr + (y * vga_info.pitch) + x * 4)) = c;
        }
    }
}
