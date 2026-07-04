ASM := nasm

C_FILES:=$(wildcard *.c)
ASM_FILES:=$(wildcard *.asm)

ASM_OBJ_FILES:=$(patsubst %.asm, $(BIN_DIR)/asm/%.o, $(ASM_FILES))
C_OBJ_FILES:=$(patsubst %.c, $(BIN_DIR)/c/%.o, $(ASM_FILES))
LDFLAGS:=-nostdlib -m elf_i386 -T linker.ld

ASMFLAGS= -f elf32
SRC_DIR:= .

.PHONY: always
$(BIN_DIR)/asm/%.o: $(SRC_DIR)/%.asm
	@echo building $@ from $<
	$(ASM) $(ASMFLAGS) $< -o $@ 

$(BIN_DIR)/c/%.o: $(SRC_DIR)/%.c
	@echo building $@ from $<
	$(CC) -c $< -o $@ $(CFLAGS)

always:
	mkdir -p $(BIN_DIR)/asm/
default: always $(ASM_OBJ_FILES) $(C_OBJ_FILES)
	@echo Building x86 assembly
