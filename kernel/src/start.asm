bits 32

%define PAGE_ALIGN 1 << 0
%define MEMORY_INFO 1 << 1
%define VIDEO_MODE 1 << 2

%define MULTIBOOT_MAGIC 0x1BADB002
MULTIBOOT_FLAGS equ PAGE_ALIGN | MEMORY_INFO | VIDEO_MODE

%define MULTIBOOT_MAGIC_KERNEL 0x2BADB002

section .multiboot
    ;multiboot spec
    align 4
    dd MULTIBOOT_MAGIC
    dd MULTIBOOT_FLAGS
    dd -(MULTIBOOT_MAGIC+MULTIBOOT_FLAGS)

    ; 0 - Framebuffer mode
    dq 0
    dq 1024
    dq 768
    dq 32

section .text

global start
extern kernel_main

start:
    cli
    mov esp, stack_space
    push eax
    push ebx
    call kernel_main
    hlt
section .bss
resb 8192
stack_space:
