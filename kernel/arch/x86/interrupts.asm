bits 32

global khalt
global are_interrupts_enabled
global enable_interrupts
global disable_interrupts

global isr_common
global spurious_interrupt
global interrupt_exception
extern interrupt_handler

global interrupt_test

extern irq_handler

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
%define IRQ_BEGIN 32
%macro IRQ_HANDLER 1
    global irq%1
    irq%1:
        push (IRQ_BEGIN + %1)
        jmp isr_common
%endmacro

IRQ_HANDLER 0
IRQ_HANDLER 1
IRQ_HANDLER 2
IRQ_HANDLER 3
IRQ_HANDLER 4
IRQ_HANDLER 5
IRQ_HANDLER 6
IRQ_HANDLER 7
IRQ_HANDLER 8
IRQ_HANDLER 9
IRQ_HANDLER 10
IRQ_HANDLER 11
IRQ_HANDLER 12
IRQ_HANDLER 13
IRQ_HANDLER 14
IRQ_HANDLER 15

isr_common:
    ;sub esp
    ;fnsave esp

    pushad
    push esp
    cld
    call interrupt_handler
    add esp, 4

    popad
    add esp, 4
    ;frstor esp
    iret

interrupt_exception:
    ;cli
    push 244
    jmp isr_common

spurious_interrupt:
    ;cli
    push 255
    jmp isr_common

interrupt_test:
    int 32
    ret
