ASM := nasm

ASM_FILES:=$(wildcard *.asm)
OBJ_FILES:=$(patsubst %.asm, $(BIN_DIR)/asm/%.o, $(ASM_FILES))
ASMFLAGS= -f elf32
SRC_DIR:= .

$(BIN_DIR)/asm/%.o: $(SRC_DIR)/%.asm
	@echo building $@ from $<
	$(ASM) $(ASMFLAGS) $< -o $@ 
always:
	mkdir -p $(BIN_DIR)/asm/
default: always $(OBJ_FILES)
	@echo Building x86 assembly
