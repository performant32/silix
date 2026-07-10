#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stddef.h>

typedef struct vector_t{
    size_t size;
    size_t capacity;
    uint8_t* data;
} vector_t;

void vector_init(vector_t* vector);
void vector_cleanup(vector_t* vector);
void vector_resize(vector_t* vector, size_t elements, size_t element_size);
void vector_reserve(vector_t* vector, size_t elements, size_t element_size);
void vector_add(vector_t* vector, void* data, size_t element_size);
#endif
