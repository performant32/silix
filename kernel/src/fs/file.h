#ifndef FILE_H
#define FILE_H

#include <stddef.h>

typedef int (*file_read_func_t)(void* address, size_t length);
typedef int (*file_write_func_t)(void* data, size_t length);

typedef struct file_t{
    file_read_func_t read;
    file_write_func_t write;
    const char* name;
} file_t;

file_t create_file(const char* name);

#endif
