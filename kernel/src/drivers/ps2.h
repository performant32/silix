#ifndef PS2_H
#define PS2_H

#include <stdint.h>

#define PS2_RW_PORT 0x60
#define PS2_STATUS_PORT 0x64
// For ps2 controller not devices
#define PS2_COMMAND_PORT 0x64

enum ps2_status_flags_e{
    PS2_OUTPUT_BUFFER=0,
    PS2_INPUT_BUFFER=1,
    PS2_SYSTEM_FLAG=2,
    // Command / Data
    PS2_CD=3,
    PS2_UNKNOWN=4,
    PS2_UNKNOWN2=5,
    PS2_TIME_OUT_ERROR=6,
    PS2_PARITY_ERROR=7
};

enum ps2_controller_commands_e{
    // Read from internal command
    PS2_READ_BYTE=0x20,
    // Read n bytes where n is the command byte & 0x1F
    PS2_READ_N=0x21,
    PS2_READ_N_MAX=0x3F,

    PS2_WRITE_BYTE=0x60,
    // Writes n bytes where n is command byte & 0x1F
    PS2_WRITE_N=0x61,
    PS2_WRITE_N_MAX=0x7F,

    // Only if two ports supported
    PS2_DISABLE_PS2_PORT=0xA7,
    PS2_ENABLE_SECOND_PORT=0xA8,

    // TODO: Rest
    // http://wiki.osdev.org/I8042_PS/2_Controller
};

void ps2_init();

uint8_t ps2_read_data_byte();
uint8_t ps2_read_status();

void ps2_issue_command(int command);

#endif
