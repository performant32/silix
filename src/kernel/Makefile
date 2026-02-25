ASM := nasm
CC:=gcc
CFLAGS:= -c -I/usr/include/efi/ -fpic -ffreestanding -fno-stack-protector -fno-stack-check -maccumulate-outgoing-args
LK := ld
ASM_FLAGS:= -f elf64
LK_FLAGS:= -T linker.ld -shared -Bsymbolic   -L/usr/lib/ -lefi -lgnuefi
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
	$(CC) $(CFLAGS) $< -o$@
kernel: always $(ASM_OBJS) $(C_OBJS)
	$(LK) $(LK_FLAGS) $(C_OBJS) $(ASM_OBJS) -o $(BIN_DIR)/kernel.bin
#	objcopy -j .test -j .sdata -j .data -j .rodata -j .dynamic -j .dynsym -j .rel -j .rela\
#		-j .rela -j .rel.* -j .rela.* -j .reloc --target efi-app-x86_64 --subsystem=10 \
#		$(BIN_DIR)/kernel.bin $(BIN_DIR)/kernel.efi
