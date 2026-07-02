#include "string.h"

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

size_t strlen(const char* data){
    size_t count = 0;
    while(data[count] != '\0')count++;
    return count;
}
void memcpy(void* destination, const void* src, size_t size){
    for(size_t i = 0; i < size; i++){
        ((char*)(destination))[i] = ((char*)(src))[i];
    }
}
void memset(void* dest, int c, size_t n){
    for(size_t i = 0; i < n; i++){
        ((int*)(dest))[i] = (int)c;
    }
}
int strcmp(char* str1, char* str2){
    size_t end1 = strlen(str1);
    size_t end2 = strlen(str2);
    for(int i = 0; i < MAX(str1, str2); i++){
        char c1 = str1[i];
        char c2 = str2[i];
        if(c1 != c2){
            return c1 - c2;
        }
    }
    return 0;
}
int strncmp(const char* str1, const char* str2, size_t n){
    for(int i = 0; i < n; i++){
        char c1 = str1[i];
        char c2 = str2[i];
        if(c1 != c2){
            return c1 - c2;
        }
    }
    return 0;
}
