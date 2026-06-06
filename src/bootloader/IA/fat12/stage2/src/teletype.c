#include "teletype.h"
#include "string.h"

void __cdecl printf(const char* format, ...){
    char buff[200];
    //memcpy(buff, format, strlen(format));
    Write(buff, 10);
}
