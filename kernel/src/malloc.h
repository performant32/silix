#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

#define HEAP_START 0x1000000
#define HEAP_END (HEAP_START + 0xFFFFF)

void kheap_init();

void* kmalloc(size_t size);
void* krealloc(void* ptr, size_t size);
void* kzmalloc(size_t size);
void kfree(void* ptr);

#endif
