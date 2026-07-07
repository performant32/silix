#ifndef IO_H
#define IO_H

#include <stdint.h>

void kprintf(char* const fmt, ...);

extern void out_port_byte(uint16_t port, uint8_t val);

extern uint8_t in_port_b(uint16_t port);
extern uint16_t in_port_w(uint16_t port);
extern uint32_t in_port_dw(uint16_t port);

void io_wait();

#endif
