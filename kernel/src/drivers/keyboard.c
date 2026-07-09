#include "keyboard.h"
#include "io.h"
#include "ps2.h"

enum keyboard_commands_e{
    KEYBOARD_ENABLE_SCAN=0xF4
};
enum response_bytes_e{
    KEYBOARD_ERROR=0x00,
    KEYBOARD_SELF_TEST_PASSED=0xAA,
    KEYBOARD_ECHO=0xEE,
    KEYBOARD_COMMAND_ACK=0xFA,
    KEYBOARD_SELF_TEST_FAILED1=0xFF,
    KEYBOARD_SELF_TEST_FAILED2=0xFD,
    KEYBOARD_RESEND=0xFE,
    KEYBOARD_DETECTION_ERROR=0xFF
};

void keyboard_init(){
    kprintf("Initialized keyboard\n");
}

void keyboard_interrupt(){
    ps2_read_data_byte();
}
