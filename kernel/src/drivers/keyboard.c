#include "keyboard.h"
#include "io.h"
#include "interrupts.h"
#include "vga.h"
#include "registers.h"
#include "i8259.h"
#include "ps2.h"
#include <stdio.h>

const char* row1 =
    "qwertyuiop"
;
const char* row2 =
    "asdfghjkl"
;
const char* row3 =
    "zxcvbnm"
;

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

//TODO: handle extended keys

void keyboard_init(){
    kprintf("Initialized keyboard\n");
    irq_install_handler(1, &keyboard_interrupt);
    // Only handling scan code set 1
}

void keyboard_interrupt(general_registers_t* registers){
    uint8_t data = ps2_read_data_byte();
    if(data == KEYBOARD_COMMAND_ACK){
        ps2_acknowledge();
        ps2_send_pending();
        return;
    }

    int button = '\0';
    if(data >= 0x10 && data <= 0x19){
        button = row1[data - 0x10];
    }
    else if(data >= 0x1E && data <= 0x26){
        button = row2[data - 0x1E];
    }
    else if(data >= 0x2c && data <= 0x32){
        button = row3[data - 0x2c];
    }
    if(button == '\0')return;
    kprintf("Keyboard issued %c\n", button);
    /*
     * TODO: handle exceptions
    int x = 5;
    kprintf("Div by 0\n", x / 0);
    */
}
