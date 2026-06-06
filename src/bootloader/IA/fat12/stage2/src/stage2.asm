bits 16
section .STAGE2
extern _start
extern _PrintString
start:
    mov ax, 0x7E0
    mov ds, ax
    call _start
.loop:
    cli
    hlt
    jmp .loop
section .data
%define ENDL `\012`, `\015`
