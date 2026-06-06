bits 16
section .code
global _PrintChar
global _PrintString
global _Write

; Args
;   char* characters
;   int size
_Write:
    enter 0
    mov cx, 0
    ;mov al, 
.loop:    
    cmp cx, [bp + 2]
    je .end
    inc cx
    jmp .loop
.end:
    leave
    ret
_PrintString:
    enter 0
    cld
    push si
    mov si, [bp+4]
    mov ah, 0x0E
.Loop:
    lodsb
    cmp al, 0
    jz .Done
    int 0x10
    jmp short .Loop
.Done:
    pop si
    leave
    ret
_PrintChar:
    enter 0
    mov ah, 0x0E
    mov al, [bp+4]
    int 0x10
    leave
    ret
