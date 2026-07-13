#ifndef TTY_H
#define TTY_H

#include <stdint.h>
#include <stddef.h>

// TODO: have multiple teletype terminals
typedef struct tty_terminal_t{
    struct{
        int columns;
        int rows;
    } size;

    struct{
        int row;
        int column;
    } position;
    // TODO: have each teletype have its own buffer for multitasking/multiuser
} tty_terminal_t;

void tty_init(tty_terminal_t* terminal);
void tty_write(tty_terminal_t* terminal, const char* str, size_t length);

tty_terminal_t* get_current_tty();

#endif
