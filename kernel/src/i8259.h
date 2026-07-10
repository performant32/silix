#ifndef I8259_H
#define I8259_H

#include <stdint.h>
void i8259_init();
void i8259_disable();
void i8259_remap(uint8_t offset1, uint8_t offset2);

void i8259_send_eoi(uint8_t irq);

uint8_t i8259_get_master_mask();
uint8_t i8259_get_slave_mask();
uint16_t i8259_get_irr();
uint16_t i8259_get_isr();

void i8259_set_mask(uint8_t irq_line);
void i8259_clear_mask(uint8_t irq_line);

#endif
