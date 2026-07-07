bits 32
global out_port_byte
global in_port_b
global in_port_w
global in_port_dw

section .text
out_port_byte:
    mov dx, [esp]
    push esi
    lea esi, [esp+4]
    outsb
    pop esi
    ret
in_port_b:
    mov eax, 0
    mov dx, [esp]
    in al, dx
    ret
in_port_w:
    mov eax, 0
    mov dx, [esp]
    in ax, dx
    ret
in_port_dw:
    mov dx, [esp]
    in eax, dx
    ret
