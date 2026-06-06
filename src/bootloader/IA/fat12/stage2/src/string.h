#ifndef STRING_H
#define STRING_H
#include "stdint.h"

int __cdecl strlen(const char* str){
    int len = 0;
    int i = 0;
    while(str[i++] != 0)len++;
    return len;
}

void __cdecl memcpy(void* dest, const void* src, int size){
    for(int i = 0; i < size; i++)
        ((uint8_t*)dest)[i] = ((uint8_t*)src)[i];
}
#endif
