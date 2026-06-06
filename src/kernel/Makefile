ASM := nasm
CC:=wcc
#CFLAGS:= -c -Iinclude/ -I/usr/include/efi/ -fpic -ffreestanding -fno-stack-protector -fno-stack-check -maccumulate-outgoing-args
CFLAGS:=-0 -zl -za -s -ecc -za99
LK := wlink
ASM_FLAGS:= -f obj
LK_FLAGS:= @linker.ld
ASM_OBJS:= $(patsubst src/%.asm, $(OBJ_DIR)/asm/%.obj, $(wildcard src/*.asm)) 
C_OBJS:= $(patsubst src/%.c, $(OBJ_DIR)/c/%.obj, $(wildcard src/*.c)) 
.PHONY: default always kernel

SRC_DIR=src

default: kernel
always:
	mkdir -p $(OBJ_DIR)/
	mkdir -p $(OBJ_DIR)/c
	mkdir -p $(OBJ_DIR)/asm
	mkdir -p $(BIN_DIR)/
$(OBJ_DIR)/asm/%.obj: $(SRC_DIR)/%.asm
	$(ASM) $(ASM_FLAGS) $< -o $@
$(OBJ_DIR)/c/%.obj: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -fo$@ -i=include
kernel: always $(ASM_OBJS) $(C_OBJS)
	$(LK) $(LK_FLAGS) file {$(C_OBJS) $(ASM_OBJS)} name $(BIN_DIR)/kernel.bin
