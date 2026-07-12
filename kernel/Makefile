ASM := nasm
CC:=gcc
LK := ld

ARCH:=x86

SRC_DIR=src
BIN_DIR:=../bin
CFILES:= $(shell find . type -printf "%P\n" -name "*.c" )
C_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/c/%.o, $(CFILES)) 
ASM_OBJS = $(patsubst arch/$(ARCH)/%.c, $(BIN_DIR)/c/%.o, $(CFILES))
CFLAGS=-ffreestanding  -fno-builtin -m32 -Wall -fno-stack-protector -no-pie -DARCH=$(ARCH) -Isrc
ASMFLAGS=-f elf32
LDFLAGS=-nostdlib -m elf_i386 -T linker.ld

ifdef IS_DEBUG
	CFLAGS += -g -O0
endif

.PHONY: default always kernel build_arch 

defualt: kernel
always:
	mkdir -p $(BIN_DIR)/
	mkdir -p $(BIN_DIR)/c/
	mkdir -p $(BIN_DIR)/c/drivers
	mkdir -p $(BIN_DIR)/c/containers
	mkdir -p $(BIN_DIR)/asm/
$(BIN_DIR)/c/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)
build_arch:
	$(MAKE) -C arch/$(ARCH)/ default ASMFLAGS="$(ASMFLAGS)" BIN_DIR="$(BIN_DIR)" CFLAGS="$(CFLAGS)"
kernel: always $(C_OBJS) build_arch
	echo $(CFILES)
	$(ASM) $(ASMFLAGS) src/start.asm -o $(BIN_DIR)/asm/start.o
	$(LK) $(LDFLAGS) -o $(BIN_DIR)/kernel $(shell find $(BIN_DIR)/ -name "*.o")
