bits 32
global load_gdt
section .text

load_gdt:
    lgdt word [esp]
    ret
