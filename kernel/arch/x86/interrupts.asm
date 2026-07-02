bits 32

section .text:
global khalt
global are_interrupts_enabled
global enable_interrupts
global disable_interrupts

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
