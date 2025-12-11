bits 16
org 0x7C00
start:
    cli
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    jmp 0x0000:main
main:
    lea si, [ds:msg_booting]
    call print_string
    
    
    call print_string
    call get_drive_parameters
    cli
    hlt
; Registers Changed
;   ah, dl
get_drive_parameters:
    mov ah, 0x8
    mov dl, 0
    int 0x13
    jnc .After
    mov si, [ds:msg_parameter_error]
.After
    mov si, [ds:msg_success]
    call print_string
    ret
; Parameters used
;   SI - source
; Registers Changed
;   
print_string:
    mov ah, 0x0e
.Loop:
    lodsb
    cmp al, 0
    je .Finish
    int 0x10
    jmp .Loop
.Finish:
    ret
times 446 - ($-$$) db 0
; Data
%define ENDL 13, 10
msg_booting: db "Booting", ENDL, 0x00
msg_parameter_error: db "Error reading drive", ENDL, 0x00
msg_success: db "Success", ENDL, 0x00
times 510 - ($-$$) db 0
;db 0x55, 0xAA
dw 0xAA55
