bits 32

; TODO: have ifdefs for the different bootloaders and their respective magic numbers
section .note.Xen
align 4
dd 4                      ; Name size
dd 8                      ; Desc size (2x 32-bit integers)
dd 18                     ; Type (XEN_ELFNOTE_PHYS32_ENTRY)
db "Xen", 0               ; Name
dd start         ; Description: Physical entry point pointer

section .text
    ;multiboot spec
    align 4
    dd 0x1BADB002;magic
    dd 0x00
    dd -(0x1BADB002+0x00)

global start
extern kernelMain

start:
    cli
    mov esp, stack_space
    call kernelMain
    hlt
section .bss
resb 8192
stack_space:
