#ifndef VGA_H
#define VGA_H
#include "multiboot.h"
#include "color.h"
#include <stdint.h>

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

// Exported font from GIMP
typedef struct gimp_image_t{
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  char         	*comment;
  unsigned char	 pixel_data[];
} gimp_image_t;

typedef struct vga_font_t{
    uint32_t width;
    uint32_t height;
    const gimp_image_t* image_data;
} vga_font_t;

extern const vga_font_t vga_8x14_font;

uint32_t vga_get_color(color_t color);
uint8_t* vga_get_framebuffer_addr();
vga_info_t* get_vga_info();

void vga_init(framebuffer_info_t* info);
void vga_draw_glyph(uint32_t x, uint32_t y, uint32_t color, uint32_t scale, char c);
void vga_set_pixel(uint32_t x, uint32_t y, uint32_t color);
void vga_clear_screen(uint32_t color);

#endif
