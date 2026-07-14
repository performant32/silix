#include "vga.h"

#include "io.h"
#include <stddef.h>
#include "string.h"

// Worst/minimal vga driver implemeentation, just assumes RGB mode and 24 bits per pixel
static vga_info_t vga_info=(vga_info_t){0};
static uint8_t* framebuffer_addr; 

extern const gimp_image_t vga_font_8x14_img;
const vga_font_t vga_8x14_font = (vga_font_t){
    8,
    14,
    &vga_font_8x14_img
};

typedef struct glyph8x8_t{
    int index;
    uint8_t data[14];
}glyph8x8_t;

uint8_t* vga_get_framebuffer_addr(){
    return framebuffer_addr;
}
vga_info_t* get_vga_info(){
    return &vga_info;
}
void draw_pixel(int x, int y, uint32_t pixel){
    framebuffer_addr[y + x] = pixel;
}
uint32_t vga_get_color(color_t color){
    return (color.r << 16) | (color.g << 8) | (color.b);
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
}

void vga_draw_glyph(uint32_t x, uint32_t y, uint32_t color, uint32_t scale, char c){
    uint8_t glyphs_per_row = 16;

    uint32_t _y = (c / glyphs_per_row);
    uint32_t _x = (c % glyphs_per_row);

    uint32_t glyph_y = _y * 14 + _y;
    uint32_t glyph_x = _x * 8 + _x + 1;

    const gimp_image_t* image_data = vga_8x14_font.image_data;
    uint8_t* pixel_data = image_data->pixel_data;
    uint8_t bytes_per_pixel = image_data->bytes_per_pixel;
    for(int j = 0; j < 14; j++){
        for(int i = 0; i < 8; i++){
            bool enabled = pixel_data[(j + glyph_y) * image_data->width * bytes_per_pixel + (glyph_x + i) * bytes_per_pixel] ? true : false;
            //bool enabled = ((glyph->data[j] >> (7 - i)) & 0x1) > 0 ? true : false;
            if(!enabled)continue;
            //vga_set_pixel(x + i, y + j, color);
            for(int _j = 0; _j < scale; _j++){
                for(int _i = 0; _i < scale; _i++){
                    vga_set_pixel(x + i * scale + _i, y + j * scale + _j, color);
                }
            }
        }
    }
}

void vga_set_pixel(uint32_t x, uint32_t y, uint32_t color){
    /// TODO: support other modes. At the moment we just assume RGB pixel mode
    framebuffer_addr[(y * vga_info.pitch) + x * (vga_info.bpp / 8) + 0] = color;
    framebuffer_addr[(y * vga_info.pitch) + x * (vga_info.bpp / 8) + 1] = color >> 8;
    framebuffer_addr[(y * vga_info.pitch) + x * (vga_info.bpp / 8) + 2] = color >> 16;
}
void vga_clear_screen(uint32_t color){
    for(int y = 0; y < vga_info.width; y++){
        for(int x = 0; x < vga_info.width; x++){
            vga_set_pixel(x, y, color);
        }
    }
}
