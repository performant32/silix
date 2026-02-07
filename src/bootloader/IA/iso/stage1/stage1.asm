bits 16
org 0x7C00
_start:
    mov al, 'a'
    mov ah, 0x0e
    int 0x10
    jmp _start
times 510-($-$$) db 0
dw 0xAA55
