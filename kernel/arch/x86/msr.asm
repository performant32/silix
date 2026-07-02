bits 32
global rdmsr

section .text:

rdmsr:
    mov ecx, eax
    rdmsr
    ret
