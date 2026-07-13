#include "tty.h"
#include "drivers/vga.h"

static tty_terminal_t main_tty=(tty_terminal_t){0};

void tty_init(tty_terminal_t* terminal){
    vga_info_t* info = get_vga_info();
    terminal->size.columns = info->width / vga_8x14_font.width;
    terminal->size.rows = info->height / vga_8x14_font.height;
    terminal->position = (typeof(terminal->position)){0};
}
void tty_write(tty_terminal_t* terminal, const char* str, size_t length){
    const vga_font_t* font_info = &vga_8x14_font;
    for(size_t i = {0u}; i < length; i++){
        char c = str[i];
        if(c == '\n'){
            terminal->position.row ++;
            terminal->position.column = 0;
            continue;
        }
        vga_draw_glyph(terminal->position.column * font_info->width, terminal->position.row * font_info->height, 0xFFFFFF, 1, c);
        terminal->position.column++;
        if(terminal->position.column >= terminal->size.columns){
            terminal->position.row ++;
            terminal->position.column = 0;
        }
    }
}
tty_terminal_t* get_current_tty(){
    return &main_tty;
}
