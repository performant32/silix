#ifndef STRING_H
#define STRING_H
#include <stddef.h>

size_t strlen(const char* data);
void memcpy(void* destination, const void* src, size_t size);
int strcmp(char* str1, char* str2);
int strncmp(const char* str1, const char* str2, size_t n);

#endif
