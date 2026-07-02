#include "io.h"

#include <stdarg.h>
#include <stdint.h>

#include "video.h"
#include "string.h"
#include "panic.h"

static bool is_digit(char c){
    return c >= '0' && c < '9';
}

static bool is_valid_number(char c, int base){
    switch(base){
    case 2:
        return c == '0' || c == '1';
    case 8:
        return c >= '0' && c <= '7';
    case 10:
        return is_digit(c);
    case 16:
        return is_digit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' || c <= 'f');
    default:
        return false;
    }
}
static char num_to_digit(int c, int base){
    switch(base){
    case 2:
    case 8:
    case 10:
        return c + '0';
    case 16:
        if(c < 10)return c + '0';
        return (c - 10) + 'A';
    }
    return '0';
}

/// assumes c is a valid number
static int to_number(char c, int base){
    switch(base){
    case 2:
    case 8:
    case 10:
        return c - '0';
    case 16:
        if(is_digit(c)){
            return c - '0';
        }
        if(c >= 'a')return (c - 'a') + 10;
        return (c - 'A') + 10;
    }
}

void kprintf(char* const fmt, ...){
    va_list args;
    va_start(args, fmt);

    char buff[1000];

    size_t len = strlen(fmt);
    size_t lastIn = 0, buffAt = 0;

    size_t at = 0;
    while(at < len){
        char c = fmt[at];
        if(c == '%'){
            size_t size = at - lastIn;
            memcpy(buff + buffAt, fmt + lastIn, size);
            buffAt+=size;
            at++;

            bool isNumber = false;
            bool isSigned = false;
            int base = 10;
            size_t number=0;

            c = fmt[at];
            switch(c){
                case 's':{
                    const char* str = va_arg(args, const char*);
                    int len = strlen(str);
                    for(size_t i = 0; i < len; i++){
                        buff[buffAt++] = str[i];
                    }
                    at++;
                    lastIn = at;
                    continue;
                }
                case 'x':{
                    isNumber = true;
                    base = 16;
                    at++;
                    number = va_arg(args, int);
                    break;
                }
                case 'b':{
                    isNumber = true;
                    base = 2;
                    at++;
                    number = va_arg(args, int);
                    break;
                }
                case 'o':{
                    isNumber = true;
                    base = 8;
                    at++;
                    number = va_arg(args, int);
                    break;
                }
                case 'd':
                case 'i':{
                    isNumber = true;
                    isSigned = true;
                    number = va_arg(args, int);
                    base = 10;
                    at++;
                    break;
                }
                case 'u':{
                    isNumber = true;
                    number = va_arg(args, int);
                    base = 10;
                    at++;
                    break;
                }
                case 'p':{
                    isNumber = true;
                    number = va_arg(args, size_t);
                    base = 16;
                    at++;
                    buff[buffAt++] = '0';
                    buff[buffAt++] = 'X';
                    break;
                }
            }
            if(isNumber){
                if(at > len){
                    kpanic();
                    return;
                }

                if(isSigned){
                    if(number < 0){
                        buff[buffAt++] = '-';
                        number = (-number) ;
                    }
                }

                char numberBuff[100];
                int count=0;

                do{
                    numberBuff[count++] = num_to_digit(number % base, base);
                    number /= base;
                }while(number > 0);

                for(int i = count-1; i >= 0; i--){
                    char c = numberBuff[i];
                    buff[buffAt++] = c;
                    //vga_write_characters(&c, 1);
                }
            }
            else{
                kpanic();
                return;
            }

            lastIn = at;
            continue;
        }
        at++;
    }
    size_t size = len - lastIn;
    memcpy(buff + buffAt, fmt + lastIn, size);
    buffAt+=size;

    vga_write_characters(buff, buffAt);
    va_end(args);
}
