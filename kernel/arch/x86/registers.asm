extern get_flags
section .text

get_flags:
    pushfd
    pop eax
    ret
