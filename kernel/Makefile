ASM := nasm
CC:=gcc
LK := ld

ARCH:=x86

SRC_DIR=src
CFILES=$(wildcard $(SRC_DIR)/*.c)
C_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/c/%.o, $(CFILES))
ASM_OBJS = $(patsubst arch/$(ARCH)/%.c, $(BIN_DIR)/c/%.o, $(CFILES))
CFLAGS=-ffreestanding  -fno-builtin -m32 -Wall -fno-stack-protector -no-pie
ASMFLAGS=-f elf32
LDFLAGS=-nostdlib -m elf_i386 -T linker.ld

.PHONY: default always kernel build_asm

defualt: kernel
always:
	mkdir -p $(BIN_DIR)/
	mkdir -p $(BIN_DIR)/c/
	mkdir -p $(BIN_DIR)/asm/
$(BIN_DIR)/c/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)
build_arch:
	$(MAKE) -C arch/$(ARCH)/ default ASMFLAGS="$(ASMFLAGS)" BIN_DIR="$(BIN_DIR)" CFLAGS="$(CFLAGS)"

kernel: always $(C_OBJS) build_arch
	$(ASM) $(ASMFLAGS) src/start.asm -o $(BIN_DIR)/asm/start.o
	@echo $(BIN_DIR)
	$(LK) $(LDFLAGS) -o $(BIN_DIR)/kernel $(wildcard $(BIN_DIR)/asm/*.o) $(wildcard $(BIN_DIR)/c/*.o)
