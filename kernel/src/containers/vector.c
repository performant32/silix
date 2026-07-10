#include "vector.h"
#include "malloc.h"
#include "string.h"

void vector_init(vector_t* vector){
    vector->size = 0;
    vector->capacity = 0;
    vector->data = NULL;
}
void vector_cleanup(vector_t* vector){
    vector->size = 0;
    vector->capacity = 0;

    kfree(vector->data);
    vector->data = NULL;
}
void vector_resize(vector_t* vector, size_t elements, size_t element_size){
    if(elements <= vector->capacity){
        vector->size = elements;
        return;
    }
    uint8_t* new_data = (uint8_t*)kmalloc(elements * element_size);
    memcpy(new_data, vector->data, vector->size * element_size);
    vector->size = elements;
    vector->capacity = elements;
    kfree(vector->data);
    vector->data = new_data;
}
void vector_reserve(vector_t* vector, size_t elements, size_t element_size){
    if(elements <= vector->capacity)return;
    uint8_t* new_data = (uint8_t*)kmalloc(elements * element_size);
    memcpy(new_data, vector->data, vector->size * element_size);
    vector->capacity = elements;
    kfree(vector->data);
    vector->data = new_data;
}
void vector_add(vector_t *vector, void *data, size_t element_size){
    vector_resize(vector, vector->size+1, element_size);
    memcpy(&vector->data[(vector->size - 1) * element_size], (uint8_t*)data, element_size);
}

