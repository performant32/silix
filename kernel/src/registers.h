#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

// TODO: have typedef and handle other architectures

enum flags_register_bits_e{
    CARRY_FLAG_BIT=0,
    RESERVED_IO_FLAG_BIT,
    RESERVED1_FLAG_BIT,
    AUXILIARY_CARRY_FLAG_BIT,
    RESERVED2_FLAG_BIT,
    ZERO_FLAG_BIT,
    SIGN_FLAG_BIT,
    TRAP_FLAG_BIT,
    INTERRUPT_ENABLED_FLAG_BIT,
    DIRECTION_FLAG_BIT,
    OVERFLOW_FLAG_BIT,
    IO_PRIVILEGE_LEVEL_FLAG_BIT=12,
    NESTED_TASK_FLAG_BIT=14,
    MODE_FLAG_BIT=15,
    // EFLAGS
    RESUME_FLAG_BIT,
    VIRTUAL_8086_MODE_FLAG_BIT,
    ALIGNMENT_CHECK_FLAG_BIT,
    VIRTUAL_INTERRUPT_FLAG_BIT,
    VIRTUAL_INTERRUPT_PENDING_FLAG_BIT,
    CPUID_ACCESS_FLAG_BIT,
    AES_KEY_SCHEDULE_LOADED_FLAG_BIT=30,
};

#define IO_FLAG_BIT_WIDTH 2

typedef struct registers_t{
    // Reverse order since struct first fields have lower memory address
    uint32_t edi;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    // Original stack pointer
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;

}__attribute__((packed)) registers_t;

typedef uint32_t flag_type;
extern flag_type get_flags();
#endif
