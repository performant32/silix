bits 32

%define PAGE_ALIGN 1 << 0
%define MEMORY_INFO 1 << 1
%define VIDEO_MODE 1 << 2
multiboot_flags equ PAGE_ALIGN | MEMORY_INFO | VIDEO_MODE

%define MULTIBOOT_MAGIC_KERNEL 0x2BADB002
section .multiboot
    ;multiboot spec
    align 4
    dd 0x1BADB002;magic
    dd multiboot_flags
    dd -(0x1BADB002+multiboot_flags)

    dq 0, 0, 0, 0, 0
    dq 1
    dq 80
    dq 25
    dq 0
section .text

global start
extern kernel_main

start:
    cli
    mov esp, stack_space
    push ebx
    call kernel_main
    hlt
section .bss
resb 8192
stack_space:
