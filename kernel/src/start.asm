bits 32

%define VGA_TEXT_MODE 1 << 2
%define BOOT_LOADER_NAME 1 << 9
%define COMMAND_LINE 1 << 2
multiboot_flags equ COMMAND_LINE | VGA_TEXT_MODE | BOOT_LOADER_NAME

%define MULTIBOOT_MAGIC_KERNEL 0x2BADB002
section .multiboot
    ;multiboot spec
    align 4
    dd 0x1BADB002;magic
    dd multiboot_flags
    dd -(0x1BADB002+multiboot_flags)
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
