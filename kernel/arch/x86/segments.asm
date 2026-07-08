extern reload_segment_registers
section .text

reload_segment_registers:
    push ebp
    mov ebp, esp
    ; Reload cs register containing code selector
    jmp 0x8:.reload_cs
.reload_cs:
    ; Reload data segment registers
    mov ax, 0x10 ; 2 is our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    leave
    ret
