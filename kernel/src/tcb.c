#include "tcb.h"
#include "malloc.h"

tcb_t* create_tcb(void* start){
    tcb_t* tcb = (tcb_t*)kzmalloc(sizeof(tcb_t));
    if(tcb){
        tcb->ip = (size_t)start;
        tcb->status = TCB_PAUSED;
    }
    return tcb;
}
