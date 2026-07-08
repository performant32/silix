bits 32

section .multiboot
    ;multiboot spec
    align 4
    dd 0x1BADB002;magic
    dd 0x00
    dd -(0x1BADB002+0x00)
section .text

global start
extern kernel_main

start:
    cli
    mov esp, stack_space
    call kernel_main
    hlt
section .bss
resb 8192
stack_space:
