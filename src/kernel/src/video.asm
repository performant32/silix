bits 16
section .code
global _SwitchMode:
    enter 0
    int 0x10
    leave
    ret
global _WritePixel:
    enter 0
    leave
    ret
