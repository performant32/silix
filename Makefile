ASM := nasm
ASM_FLAGS := -f bin
OBJ_DIR:=bin/objs
BIN_DIR:=bin
ISO_DIR:=bin/iso
BOOT_SRC:=src/boot
KERNEL_SRC:=src/kernel
BOOTLOADER_SOURCES:= $(patsubst $(OBJ_DIR)/%.asm, $src/boot/%.asm, $(wildcard src/boot/*.asm))
BOOT_OPTIONS:=

.PHONY: default build_floppy run_floppy boot1 run_nographic clean fat12

default: build_floppy run_floppy

clean:
	rm -rf bin
make_files:
	echo $(wildcard src/boot/*.asm)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(ISO_DIR)
build_floppy: make_files boot1
	dd if=/dev/zero of=bin/silix.floppy bs=512 count=2734
	mkfs.fat -F 12 bin/silix.floppy 
	echo "Hello MFat12Hello" | mcopy -i bin/silix.floppy - ::/source.txt 
	#dd if=$(OBJ_DIR)/boot1.bin of=bin/silix.floppy bs=512 count=1 conv=notrunc

boot1:
	$(ASM) $(ASM_FLAGS) $(BOOT_SRC)/boot1.asm -o $(OBJ_DIR)/boot1.bin
run_floppy:
	qemu-system-x86_64 $(BOOT_OPTIONS) -fda bin/silix.floppy 
fat12:
	$(MAKE) -C tools/fat12/ fat12 OUTPUT_DIR=$(abspath bin/tools)
