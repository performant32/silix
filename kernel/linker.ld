OUTPUT_FORMAT(elf32-i386)
    ENTRY(start)
    SECTIONS
    {
        .text 0x100000 : { *(.multiboot) *(.text) }
        .data : { *(.data) }
        .bss : { *(.bs) }
        .rodata : { *(.rodata) }
    }
