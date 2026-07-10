#include "pit.h"
#include "io.h"
#include <stdint.h>

void pit_init(){
    // uint16_t reload_value = PIT_SPEED_HZ / 1;
    // uint8_t command = 0b00110110;
    // out_port_byte(PIT_MODE_COMMAND_REGISTER, command);
    // out_port_byte(PIT_CHANNEL_0_DATA_PORT, reload_value & 0xFF);
    // out_port_byte(PIT_CHANNEL_0_DATA_PORT, reload_value >> 8);
    // kprintf("Initialized PIT with command 0x%x\n", command);
}
