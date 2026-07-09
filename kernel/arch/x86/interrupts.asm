bits 32

global khalt
global are_interrupts_enabled
global enable_interrupts
global disable_interrupts
global isr_wrapper
global interrupt_fault_wrapper
global interrupt_trap_wrapper
global interrupt_abort_wrapper
global interrupt_test

extern interrupt_handler

section .text

khalt:
    hlt
    jmp khalt
are_interrupts_enabled:
    pushfd
    pop eax
    and eax, 0x200
    shr eax, 9
    ret

enable_interrupts:
    sti
    ret
disable_interrupts:
    cli
    ret

isr_wrapper:
    ;sub esp
    ;fnsave esp
    pushad
    cld
    call interrupt_handler
    popad
    ;frstor esp
    iret
interrupt_fault_wrapper:
    iret
interrupt_trap_wrapper:
    iret
interrupt_abort_wrapper:
    iret
interrupt_test:
    int 32
    ret
