#include "tty.h"
#include "drivers/vga.h"
#include "string.h"
#include "malloc.h"
#include "io.h"
#include <stddef.h>
#include <string.h>

static tty_terminal_t main_tty=(tty_terminal_t){0};

void tty_init(tty_terminal_t* terminal){
    vga_info_t* info = get_vga_info();
    terminal->size.columns = info->width / vga_8x14_font.width;
    terminal->size.rows = info->height / vga_8x14_font.height;
    terminal->position = (typeof(terminal->position)){0};
    terminal->background_color = (color_t){0,0,255};
    terminal->text_color = (color_t){255};

    terminal->lines = kmalloc(sizeof(char*) * terminal->size.rows);
    for(size_t j = 0; j < terminal->size.rows + 1; j++){
        terminal->lines[j] = kzmalloc(terminal->size.columns+1);
    }
    tty_clear_screen(terminal);
    kprintf("TTY rows %i, columns %i\n", terminal->size.rows, terminal->size.columns);
}
void tty_clear_screen(tty_terminal_t *terminal){
    color_t bg = terminal->background_color;
    uint32_t color = vga_get_color(bg);
    for(size_t i = 0; i < terminal->size.rows; i++){
        memset(terminal->lines[i], '\0', sizeof(char));
    }
    vga_clear_screen(color);
}
void tty_write(tty_terminal_t* terminal, const char* str, size_t length){
    const vga_font_t* font_info = &vga_8x14_font;

    color_t fg = terminal->text_color;
    uint32_t color = vga_get_color(fg);

    for(size_t i = {0u}; i < length; i++){
        char c = str[i];
        if(c == '\n'){
            terminal->position.row ++;
            terminal->position.column = 0;
            if(terminal->position.row >= terminal->size.rows){
                tty_scroll_down(terminal);
            }
            continue;
        }


        char* line = terminal->lines[terminal->position.row];
        size_t column = strlen(line);
        memset(line + column, c, sizeof(char));
        vga_draw_glyph(column * font_info->width, terminal->position.row * font_info->height, color, 1, c);
        terminal->position.column = column;

        if(terminal->position.column >= terminal->size.columns){
            terminal->position.row ++;
            terminal->position.column = 0;
            if(terminal->position.row >= terminal->size.rows){
                tty_scroll_down(terminal);
            }
        }


    }
}
void tty_scroll_down(tty_terminal_t* terminal){
    if(terminal->position.row <= 0)return;

    memset(terminal->lines[terminal->position.row], '\0', sizeof(char));
    ptrdiff_t start = terminal->position.row - 1;
    for(ptrdiff_t j = 0; j < start; j++){
        char* below = terminal->lines[j+1];
        memcpy(terminal->lines[j], below, strlen(below) + 1);
        //memcpy(terminal->lines[j], below, strlen(below) + 1);
    }
    for(size_t j = start; j < terminal->size.rows; j++){\
        char* line = terminal->lines[j];
        memset(line, '\0', sizeof(char));
    }
    vga_clear_screen(vga_get_color(terminal->background_color));
    const vga_font_t* font_info = &vga_8x14_font;

    uint32_t color = vga_get_color(terminal->text_color);

    for(size_t j = 0; j < terminal->size.rows; j++){
        char* line = terminal->lines[j];
        size_t len = strlen(line);
        for(size_t i = 0; i < len; i++)
            vga_draw_glyph(i * font_info->width, j * font_info->height, color, 1, line[i]);

    }
    terminal->position.row--;
    terminal->position.column=0;
    memset(terminal->lines[terminal->position.row], '\0', terminal->size.columns* sizeof(char));
}
tty_terminal_t* get_current_tty(){
    return &main_tty;
}
