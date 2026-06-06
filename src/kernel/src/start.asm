bits 16
section .KERNEL_START
global _kend
extern _kmain
_start:
    mov ah, 0x0e
    mov al, '8'
    int 0x10
    cli
    hlt
    call _kmain
_kend:
    cli
    hlt
db "HELLO WORLD KERNEL"
