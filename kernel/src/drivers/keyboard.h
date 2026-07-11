#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "registers.h"

extern const char* scan_code_1;
void keyboard_init();
void keyboard_interrupt(general_registers_t* registers);

#endif
