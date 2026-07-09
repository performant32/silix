#include "ps2.h"
#include "io.h"

void ps2_init(){
    kprintf("Initialized ps2\n");
}

uint8_t ps2_read_status(){
    return in_port_b(PS2_STATUS_PORT);
}

uint8_t ps2_read_data_byte(){
    uint8_t status = ps2_read_status();

    return in_port_b(PS2_RW_PORT);
}

void ps2_issue_command(int command){

}
