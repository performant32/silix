#include "ps2.h"
#include "io.h"
#include "containers/vector.h"
#include <stddef.h>

//vec<uint8_t>
static vector_t commands_to_issue=(vector_t){0};
static bool can_issue_command = false;

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

void ps2_send_pending(){
    if(commands_to_issue.size < 1)return;
    out_port_byte(PS2_COMMAND_PORT, ((uint8_t*)commands_to_issue.data)[0]);
}
void ps2_acknowledge(){
    if(commands_to_issue.size < 1)return;
    uint8_t* data = commands_to_issue.data;
    for(size_t i = 0; i < commands_to_issue.size - 1; i++){
        data[i] = data[i + 1];
    }
    commands_to_issue.size--;
}
void ps2_issue_command(uint8_t command){
    if(can_issue_command){
        out_port_byte(PS2_COMMAND_PORT, command);
        can_issue_command = false;
        return;
    }
    vector_add(&commands_to_issue, &command, sizeof(uint8_t));
}
