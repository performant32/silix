#include "multiboot.h"

bool multiboot1_has_mmap(multiboot1_header_t* multiboot){
    return multiboot->flags & SBIT(MULTIBOOT_MMAP_BIT);
}
