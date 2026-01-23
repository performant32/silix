ENTRY (kmain)

SECTIONS{
    . = 0x00100000;
    .boot_section :{
        *(.multiboot)
    }

    .text : ALIGN(0x1000){
        *(.text)
    }


    .data : ALIGN(0x1000){
        *(.data)
    }
    .bss : ALIGN(0x1000){
        *(.bss)
    }
}
