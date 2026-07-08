#include "ps2.h"
#include "io.h"

void ps2_init(){
    kprintf("Initialized ps2\n");
}

void ps2_read_byte(){
    in_port_b(PS2_PORT);
}
