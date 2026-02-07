ASM := nasm
CC:=gcc
CFLAGS:= -c -I/usr/include/efi/ -fpic -ffreestanding -fno-stack-protector -fno-stack-check -maccumulate-outgoing-args
LK := ld
ASM_FLAGS:= -f elf64
#CFLAGS:=-shared -Wl,--subsystem,efi-application -m64 -e kmain -nostdlib \
		-fno-stack-protector -fpic -fshort-wchar -mno-red-zone
LK_FLAGS:= -T linker.ld -shared -Bsymbolic   -L/usr/lib/ -lefi -lgnuefi
.PHONY: default always kernel
defualt: kernel
always:
	mkdir -p $(BIN_DIR)/
kernel: always
	$(echo "HELLO")
	$(CC) $(CFLAGS) src/kernel.c -o $(BIN_DIR)/kernel.obj
#$(ASM) $(ASM_FLAGS) src/multiboot.asm -o $(BIN_DIR)/multiboot.obj
	$(LK) $(LK_FLAGS)  $(BIN_DIR)/kernel.obj -o $(BIN_DIR)/kernel.bin
	objcopy -j .test -j .sdata -j .data -j .rodata -j .dynamic -j .dynsym -j .rel -j .rela\
		-j .rela -j .rel.* -j .rela.* -j .reloc --target efi-app-x86_64 --subsystem=10 \
		$(BIN_DIR)/kernel.bin $(BIN_DIR)/kernel.efi
