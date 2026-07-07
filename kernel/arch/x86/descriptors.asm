bits 32
global load_gdt
global load_idt
section .text

load_gdt:
    mov eax, [esp+4]
    lgdt [eax]

    ; Reload data segment registers
    mov ax, 0x10 ; 2 is our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x8:.reload_cs
.reload_cs:
    ret

load_idt:
    mov eax, [esp+4]
    lidt [eax]
    ret
