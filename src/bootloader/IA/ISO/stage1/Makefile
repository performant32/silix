ASM:=nasm
ASM_FLAGS:=-f win32

BIN_DIR:=
OBJ_DIR:=

.PHONY: always stage1
always:
	mkdir -p $(BIN_DIR)
stage1: always
	$(ASM) $(ASM_FLAGS) stage1.asm -o $(BIN_DIR)/stage1.obj
