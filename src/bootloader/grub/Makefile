ASM=NASM
CC=wcc

.PHONY: default always build
default: build
always:
	echo $(BIN_DIR)
	mkdir -p $(BIN_DIR)/iso/boot/grub/
build: always
	echo "Building iso"
	cp $(KERNEL_BIN)/kernel.bin $(BIN_DIR)/iso/boot/silix.exe
	cp grub.cfg $(BIN_DIR)/iso/boot/grub/grub.cfg
	grub-mkrescue -p /boot -o $(BIN_DIR)/silix.iso $(BIN_DIR)/iso
