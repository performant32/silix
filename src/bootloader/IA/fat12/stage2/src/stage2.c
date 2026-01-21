#include "teletype.h"

#define ENDL "\12 \15"
extern void print();
void start(){
    PrintString("Hello Stage2" ENDL);
    PrintString("Done" ENDL);
    int i = 0;
    for(; i < 67; i++){
        int temp={i};
        char c = (char)temp % 10 + '0';
        PrintChar('0' + sizeof(int));
        //Write(ENDL, 2);
    }
}
