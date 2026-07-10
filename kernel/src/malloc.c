#include "malloc.h"
#include <stdint.h>
#include "panic.h"

// Yes very simple heap

typedef struct heap_block_t{
    bool is_free; 
    // Must be set if not free
    void* next;
} heap_block_t;

heap_block_t *heap_start = (heap_block_t*)HEAP_START;

void kheap_init(){
    heap_start->is_free = true;
    heap_start->next = NULL;
}

void* kmalloc(size_t size){
    heap_block_t* current_block = heap_start;
    while(true){
        if(current_block->is_free){
            if(current_block->next == NULL){
                current_block->is_free = false;

                heap_block_t* next_block = (heap_block_t*)((size_t)current_block + sizeof(heap_block_t) + size);
                if((size_t)next_block >= HEAP_END){
                    return NULL;
                }

                next_block->is_free = true;
                next_block->next = NULL;

                current_block->next = next_block;
                return (void*)((size_t)current_block + sizeof(heap_block_t));
            }

            size_t block_size = (size_t)current_block->next - (size_t)current_block;
            if(block_size >= size + sizeof(heap_block_t)){
                current_block->is_free = false;
                heap_block_t* next_block = (heap_block_t*)((size_t)current_block + sizeof(heap_block_t) + size);
                if((size_t)next_block >= HEAP_END){
                    return NULL;
                }
                next_block->is_free = true;
                next_block->next = NULL;

                current_block->next = next_block;
                return (void*)((size_t)current_block + sizeof(heap_block_t));
            }
        }
        current_block = current_block->next;
    }
    return NULL;
}
void kfree(void* ptr){
    if(!ptr)return;
    heap_block_t* heap_block = (heap_block_t*)((size_t)(ptr) - sizeof(heap_block_t));
    heap_block->is_free = true;
}
