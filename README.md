# SILIX
An i386 operating system being developed in my freetime for fun and to learn

## Prerequisites
1. Cross platform arm compiler
2. nasm
3. GCC
4. gnu make
5. python

## Building 
Generate the kernel image into `bin/IA/kernel`:  
`make kernel`  

## Running
Copies the kernel image with a bootable filename for qemu
runs kernel directly with --kernel flag:
`make run_kernel`  

## Booting
Currently we are booting the kernel image directly with qemu with multi boot specification

## Current Features

## Future Features
* Interrupts
* PCI & PCIE support
* USB Support
* Graphics Mode
* VFS
* Fat32 or Fat16

