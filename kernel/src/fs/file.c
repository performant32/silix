#include "file.h"

#include "malloc.h"
#include "string.h"

file_t create_file(const char* name){
    file_t file = (file_t){0};
    int len = strlen(name);
    char* data = (char*)kmalloc(len+1);
    memcpy(data, name, len);
    data[len] = '\0';
    file.name = data;
    return file;
}
