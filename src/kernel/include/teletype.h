#ifndef TELETYPE_H
#define TELETYPE_H

extern void __cdecl PrintString(const char* string);
extern void __cdecl PrintChar(char c);
extern void __cdecl Write(const char* string, int len);
void __cdecl printf(const char* string, ...);

#define ENDL "\12\15"
#endif
