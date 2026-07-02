bits 32

section .text:
global khalt
khalt:
    cli
    hlt
    jmp khalt
