# SILIX
An i386 operating system being developed in my freetime for fun and to learn

## Prerequisites
1. Cross platform arm compiler
2. nasm
3. GCC
4. gnu make
5. python
6. xorisso
6. mtools

## Building 
Generate the kernel image into `bin/IA/kernel`:  
`make kernel`  

## Run kernel directly
Copies the kernel image with a bootable filename for qemu  
runs kernel directly with --kernel flag:
`make run_kernel`  

## Create ISO
Builds the kernel and packages it withing an iso right after  
`make iso`

## Run ISO
Runs a packaged ISO in the kernel bin directory  
`make run_iso`

## Booting
Currently we are booting the kernel image directly with qemu with multi boot specification

## Current Features
* PIC Support(i8259)
* VGA Text support

## Future Features
* Interrupts through APIC
* PCI & PCIE support
* USB Support
* Graphics Mode(VGA)
* VFS
* Fat32 or Fat16
* UserMode/Ring3
* System Calls
* GPU Driver

## Supported Architectures
* x86

## Future Architectures
* x86_64
* arm64
