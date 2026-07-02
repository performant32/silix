#ifndef VIDEO_H
#define VIDEO_H

#include <stddef.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

void vga_clear_screen();
void vga_set_character(int column, int row, char c);
void vga_write_characters(char* const data, size_t size);

int getCursor();
#endif
