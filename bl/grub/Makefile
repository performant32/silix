ASM=nasm
VERSION:=001
.PHONY: default always build

default: build
always:
	echo $(BIN_DIR)
	mkdir -p $(BIN_DIR)/iso/boot/grub/
build: always
	echo "Building iso for kernel-$(VERSION)"
	cp $(KERNEL_BIN)/kernel-$(VERSION) $(BIN_DIR)/iso/boot/silix.elf
	cp grub.cfg $(BIN_DIR)/iso/boot/grub/grub.cfg
	grub-mkrescue -p /boot -o $(BIN_DIR)/silix.iso $(BIN_DIR)/iso
