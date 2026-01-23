ASM := nasm
LK := ld
ASM_FLAGS := -f elf32

CC:=x86_64-w64-mingw32-c++
CFLAGS:=-shared -Wl,--subsystem,efi-application -m64 -e kmain -nostdlib \
		-fno-stack-protector -fpic -fshort-wchar -mno-red-zone
LK_FLAGS:= -T linker.ld -m elf_i386
.PHONY: default always kernel
defualt: kernel
always:
	mkdir -p $(BIN_DIR)/
kernel: always
	$(ASM) $(ASM_FLAGS) src/kernel.asm -o $(BIN_DIR)/kernel.obj
	$(LK) $(LK_FLAGS)  $(BIN_DIR)/kernel.obj -o $(BIN_DIR)/kernel.bin
	#$(CC) $(CFLAGS) $(BIN_DIR)/kernel.bin -o $(BIN_DIR)/kernel.exe
