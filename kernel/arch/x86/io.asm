bits 32
global out_port_byte
global in_port_b
global in_port_w
global in_port_dw

section .text
out_port_byte:
    mov dx, [esp+4]
    push esi
    lea esi, [esp+12]
    outsb
    pop esi
    ret
out_port_word:
    mov dx, [esp+4]
    push esi
    lea esi, [esp+12]
    outsw
    pop esi
    ret
in_port_b:
    mov eax, 0
    mov dx, [esp+4]
    in al, dx
    ret
in_port_w:
    mov eax, 0
    mov dx, [esp+4]
    in ax, dx
    ret
in_port_dw:
    mov dx, [esp+4]
    in eax, dx
    ret
