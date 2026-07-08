bits 32

global khalt
global are_interrupts_enabled
global enable_interrupts
global disable_interrupts
global isr_wrapper
global interrupt_test

extern interrupt_handler

section .text

khalt:
    cli
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
    pushad
    cld
    call interrupt_handler
    popad
    iret
interrupt_test:
    int 33
    ret
