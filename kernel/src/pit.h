#ifndef PIT_H
#define PIT_H
#include "interrupts.h"
#include "registers.h"

// Intel 8253/8254
//
// Oscillator, prescaler and 3 independent frequency dividers

// Obseleted by HPET and ACPI

#define PIT_SPEED_MHZ 1.193182
#define PIT_SPEED_HZ (PIT_SPEED_MHZ * 1000000)

// Bit 0
#define PIT_CHANNEL_2_PORT 0x61

// IO Ports
#define PIT_CHANNEL_0_DATA_PORT 0x40
#define PIT_CHANNEL_1_DATA_PORT 0x41
#define PIT_CHANNEL_2_DATA_PORT 0x42
#define PIT_MODE_COMMAND_REGISTER 0x43


// PIT Command bits
#define PIT_SELECT_CHANNEL_BIT 6
#define PIT_SELECT_CHANNEL_BIT_WIDTH 2

#define PIT_ACCESS_MODE_BIT 4
#define PIT_ACCESS_MODE_BIT_WIDTH 2

#define PIT_OPERATING_MODE_BIT 1
#define PIT_OPERATING_MODE_BIT_WIDTH 3

#define PIT_BCD_MODE_BIT 0

// Channel 0 is connected directly to irq0
//
// Channel 1 is unusable(might not even exist)
// Channel 2 is connected to pc speaker
// 
void pit_init();
void pit_interrupt(general_registers_t* registers);
#endif
