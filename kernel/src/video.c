#include "video.h"

static char* videoMemoryPtr = (char*)0xB8000;
static int column = 0;
static int row = 0;

void vga_clear_screen(){
    int j = 0;
    while(j < VGA_HEIGHT * VGA_WIDTH * 2){
        videoMemoryPtr[j] = ' ';
        videoMemoryPtr[j+1] = 0x02;
        j = j+2;
    }
    row=0;
    column=0;
}
void vga_set_character(int column, int row, char c){
    videoMemoryPtr[2 * (row * VGA_WIDTH + column)] = c;
    videoMemoryPtr[2 * (row * VGA_WIDTH + column) + 1] = 0x02;
}

void vga_write_characters(char* const data, size_t size){
    for(size_t i = 0; i < size; i++){
        char c = data[i];
        if(c == '\n'){
            row++;
            column=0;
            continue;
        }
        vga_set_character(column, row, c);
        column++;
        if(column >= VGA_WIDTH){
            column=0;
            row++;
            if(row >= VGA_HEIGHT){
                vga_clear_screen();
            }
        }
    }
}
