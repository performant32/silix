#ifndef TCB_H
#define TCB_H

#include <stddef.h>
#include "registers.h"

enum tcb_status:int{
    TCB_PAUSED=0,
    TCB_STARTED
};

typedef struct tcb_t{
    general_registers_t cpu_registers;
    size_t ip;
    enum tcb_status status;
    void* kernel_stack;
}__attribute__((packed)) tcb_t;

tcb_t* create_tcb(void* start);


#endif
