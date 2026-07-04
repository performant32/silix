OUTPUT_FORMAT(elf32-i386)
    ENTRY(start)
    SECTIONS
    {
        .text 0x100000 : { *(..note.Xen) *(.text) }
        .data : { *(.data) }
        .bss : { *(.bs) }
    }
