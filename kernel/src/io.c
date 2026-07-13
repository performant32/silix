#include "io.h"

#include <stdarg.h>
#include <stdint.h>
#include <limits.h>

#include "string.h"
#include "panic.h"
#include "tty.h"

#define MIN(a,b) (a < b ? a : b)
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

            bool is_number = false;
            bool is_signed = false;
            int base = 10;
            size_t number=0;
            bool padded = false;
            bool left_aligned = false;
            int min_padding = 0;
            int max_precision = INT_MAX;

            c = fmt[at];
            if(c == '.'){
                at++;
                c = fmt[at];
                if(c == '*'){
                    max_precision = (int)va_arg(args, int);
                    at++;
                }
                c = fmt[at];
            }
            if(c == '*'){
                min_padding = (int)va_arg(args, int);
                at++;
            }
            c = fmt[at];
            switch(c){
                case 'c':{
                    buff[buffAt++] = (char)va_arg(args, int);
                    lastIn = ++at;
                    continue;
                }
                case 's':{
                    const char* str = va_arg(args, const char*);

                    int len = max_precision;
                    if(len == INT_MAX){
                        len = strlen(str);
                    }
                    for(size_t i = 0; i < len; i++){
                        buff[buffAt++] = str[i];
                    }
                    lastIn = ++at;
                    continue;
                }
                case 'x':{
                    is_number = true;
                    base = 16;
                    at++;
                    number = va_arg(args, int);
                    break;
                }
                case 'o':{
                    is_number = true;
                    base = 8;
                    at++;
                    number = va_arg(args, int);
                    break;
                }
                case 'd':
                case 'i':{
                    is_number = true;
                    is_signed = true;
                    // int num = (int)va_arg(args, int);
                    // if(num < 0){
                    //     number |= (1 << (sizeof(size_t) * 8 - 1));
                    // }
                    //number |= num & ((1 << (sizeof(int) * 8 - 1)) - 1);
                    number = va_arg(args, int);
                    base = 10;
                    at++;
                    break;
                }
                case 'u':{
                    is_number = true;
                    number = va_arg(args, unsigned int);
                    base = 10;
                    at++;
                    break;
                }
                case 'b':{
                    is_number = true;
                    number = va_arg(args, unsigned int);
                    base = 2;
                    at++;
                    break;
                }
                case 'p':{
                    is_number = true;
                    number = va_arg(args, size_t);
                    base = 16;
                    at++;
                    buff[buffAt++] = '0';
                    buff[buffAt++] = 'X';
                    padded = true;
                    left_aligned = true;
                    min_padding = sizeof(size_t) * 2;
                    
                    break;
                }
            }
            if(is_number){
                if(at > len){
                    kpanic();
                    return;
                }

                if(is_signed){
                    int* num = &number;
                    if(*num < 0){
                        buff[buffAt++] = '-';
                        number = -(*num);
                    }
                }

                char numberBuff[100];
                int count=0;

                do{
                    numberBuff[count++] = num_to_digit(number % base, base);
                    number /= base;
                }while(number != 0);

                if(padded && left_aligned){
                    for(int i = count; i < min_padding - count; i++){
                        buff[buffAt++] = '0';
                    }
                }

                int lastIndex = count - 1;
                //for(int i = lastIndex; i >= 0; i--){
                for(int i = 0; i < MIN(count, max_precision); i++){
                    char c = numberBuff[lastIndex - i];
                    //char c = numberBuff[i];
                    buff[buffAt++] = c;
                }

                if(padded && !left_aligned){
                    for(int i = count; i < min_padding - count; i++){
                        buff[buffAt++] = '0';
                    }
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

    tty_terminal_t* terminal = get_current_tty();
    tty_write(terminal, buff, buffAt);
    va_end(args);
}

void io_wait(){
    out_port_byte(0x80, 0);
}
