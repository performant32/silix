# SILIX
An i386 operating system being developed in my freetime for fun and to learn  
Yes I know the code probably sucks(decided to move abstracting hardware like pic's for now which I know ill regret later when I want to add more architectures like arm)

## Prerequisites
1. Cross platform arm compiler
2. nasm
3. GCC
4. gnu make
5. python
6. xorisso
7. mtools
8. GCC EFI Stubs
9. grub(for porting to iso)

## Creating a Config
The way config files are handled with Silix is with dotfiles ending with .smk(silix makefiles)  
to generate these make files just run  
`make config`

## Configuration Abilities  
Is Debug - Generates debug builds for gdb and has qemu wait for debugger to connect on boot  
Is Graphic - Wether you want qemu to run in a window or in the terminal(debugging over ssh for example, although havent created vga support for terminal so its basically useless)  

## Building kernel image
Generate the kernel image into `bin/IA/kernel`:  
`make kernel`  

## Creating the ISO
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


## Kernel Architecture
(Not too much thought on yet sadly due to getting basic hardware features working)  
* Monolithic Kernel - I have decided that most parts of the kernel will be running in kernel space for performance
* Modular Kernel - The kernel should have support for loading kernels for custom drivers in the future(like if you want to create a controller that isnt supported yet) This feature is a fever dream considering the kernel isn't even in a working stage for tasks  
* Tasks - The kernel so far will be using a Round Robin style of context switching(for simplicity until other parts of the kernel are more fleshed out)  

## Kernel Design
1. Where are kernel files stored? Kernel specific files are stored in the kernel/ folder  
Inside this folder stores Makefiles for kernel image generation(eg .*.smk, Makefile, linker.ld)
2. Drivers are stored in a sub folder called drivers
