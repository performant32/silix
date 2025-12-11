ASM := nasm
ASM_FLAGS := -f bin
OBJ_DIR:=bin/objs
BIN_DIR:=bin
ISO_DIR:=bin/iso
BOOT_SRC:=src/boot
KERNEL_SRC:=src/kernel
BOOTLOADER_SOURCES:= $(patsubst $(OBJ_DIR)/%.asm, $src/boot/%.asm, $(wildcard src/boot/*.asm))

.PHONY: build run

default: build run
make_files:
	echo $(wildcard src/boot/*.asm)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(ISO_DIR)
build: make_files boot1
	mkisofs -o $(BIN_DIR)/silix.iso -r -b boot1.bin -no-emul-boot $(ISO_DIR)
boot1:
	$(ASM) $(ASM_FLAGS) $(BOOT_SRC)/boot1.asm -o $(ISO_DIR)/boot1.bin
run:
	qemu-system-i386 -cdrom bin/silix.iso -boot d
