#include "pit.h"
#include "interrupts.h"
#include "io.h"
#include <stdint.h>
#include "drivers/vga.h"

void pit_init(){
    uint16_t reload_value = 65535;
    uint8_t command = 0b00110110;
    out_port_byte(PIT_MODE_COMMAND_REGISTER, command);
    out_port_byte(PIT_CHANNEL_0_DATA_PORT, reload_value & 0xFF);
    out_port_byte(PIT_CHANNEL_0_DATA_PORT, reload_value >> 8);
    irq_install_handler(0, pit_interrupt);
    kprintf("Initialized PIT with command 0x%x\n", command);
}
void pit_interrupt(general_registers_t* registers){
    //kprintf("PIT Test\n");
    // TODO: Task switch
}
