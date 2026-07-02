bits 16
section .STAGE2
extern _start
extern _PrintString
start:
    mov al, 'T'
    mov ah, 0x0E
    int 0x10

    mov ax, 0x7E0
    mov ds, ax
    call _start

    push test
    call _PrintString
section .data
%define ENDL `\012`, `\015`
test: db "Fully Loaded",ENDL, 0
