#include "i8259.h"

#include "io.h"
#include <stddef.h>
#include "interrupts.h"

#define MASTER_PIC_COMMAND 0x20
#define MASTER_PIC_DATA 0x21
#define SLAVE_PIC_COMMAND 0xA0
#define SLAVE_PIC_DATA 0xA1

// ICW4 will be present
#define ICW1_ICW4 0x01
#define ICW1_SINGLE 0x02    // SIngle cascade mode
#define ICW1_INTERVAL 0x04 // call address interval
#define ICW1_LEVEL 0x08 // Level triggered edge mode
#define ICW1_INIT 0x10 // Initialization - Required

#define ICW4_8086   0x01 // 8086/88 mode
#define ICW4_AUTO   0x02        // AUTO(normal) EOI
#define ICW4_BUF_SLAVE  0x08            // Buffered mode/slave
#define ICW4_BUF_MASTER 0x0C            //  Buffered mode/master
#define ICW4_SFNM           0x10            // Special Fully nested(not)
#define CASCADE_IRQ 2

#define PIC_EOI 0x20

void i8259_init(){
    i8259_remap(32, 40);
    kprintf("Initialized Intel 8259 PIC\n");
}
void i8259_remap(int offset1, int offset2){
    out_port_byte(MASTER_PIC_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    out_port_byte(SLAVE_PIC_COMMAND, ICW1_INIT | ICW1_ICW4);

    io_wait();
    out_port_byte(MASTER_PIC_DATA, offset1); // offset1 is vector offset
    io_wait();
    out_port_byte(SLAVE_PIC_DATA, offset2); // offset2 is vector offset
    io_wait();

    out_port_byte(MASTER_PIC_DATA, 1 << CASCADE_IRQ); // Tell master pic that there is a slave at irq 2
    io_wait();

    out_port_byte(SLAVE_PIC_DATA, CASCADE_IRQ); // Tell slave its identity
    io_wait();

    // Have both use 8086 mode instead of 8080
    out_port_byte(MASTER_PIC_DATA, ICW4_8086);
    io_wait();
    out_port_byte(SLAVE_PIC_DATA, ICW4_8086);

    // Unmask both controllers
    out_port_byte(MASTER_PIC_DATA, 0);
    out_port_byte(SLAVE_PIC_DATA, 0);
    i8259_clear_mask(1);
    kprintf("Initialized 8259 with master vector offset %d and slave %d\n", offset1, offset2);
}
void i8259_disable(){
    out_port_byte(MASTER_PIC_DATA, 0xFF);
    out_port_byte(SLAVE_PIC_DATA, 0xFF);
    kprintf("Disabled I8259\n");
}

void i8259_send_eoi(uint8_t irq){
    if(irq >= 8)
        out_port_byte(SLAVE_PIC_COMMAND, PIC_EOI);
    out_port_byte(MASTER_PIC_COMMAND, PIC_EOI);
}

uint8_t i8259_get_master_mask(){
    return in_port_b(MASTER_PIC_DATA);
}

uint8_t i8259_get_slave_mask(){
    return in_port_b(SLAVE_PIC_DATA);
}

void i8259_set_mask(uint8_t irq_line){
    uint16_t port;
    uint8_t value;

    if(irq_line < 8){
        port = MASTER_PIC_DATA;
    }else{
        port = SLAVE_PIC_DATA;
        irq_line -= 8;
    }
    value = in_port_b(port) | (1 << irq_line);
    out_port_byte(port, value);
}
void i8259_clear_mask(uint8_t irq_line){
    uint16_t port;
    uint8_t value;

    if(irq_line < 8){
        port = MASTER_PIC_DATA;
    }else{
        port = SLAVE_PIC_DATA;
        irq_line -= 8;
    }
    value = in_port_b(port) & ~(1 << irq_line);
    out_port_byte(port, value);
}
