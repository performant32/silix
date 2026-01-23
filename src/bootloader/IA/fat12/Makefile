OUTPUT_DIR:=$(BIN_DIR)/floppy
OBJ_DIR=$(OUTPUT_DIR)/objs
clean:
	rm -rf $(OUTPUT_DIR)
make_files:
	mkdir -p $(OBJ_DIR)
build_floppy: make_files stage1 stage2 test
	dd if=/dev/zero of=$(OUTPUT_DIR)/silix.floppy bs=512 count=2880
	mkfs.fat -F 12 $(OUTPUT_DIR)/silix.floppy 
	mcopy -i $(OUTPUT_DIR)/silix.floppy $(STAGE2_BIN)/stage2.bin ::/STAGE2.bin
	dd if=$(STAGE1_BIN)/stage1.bin of=$(OUTPUT_DIR)/silix.floppy bs=512 count=1 conv=notrunc
	mcopy -i $(OUTPUT_DIR)/silix.floppy $(BIN_DIR)/test.bin ::/TEST.BIN

stage1:
	$(MAKE) -C $(BOOTLOADER_SRC)/stage1 stage1 OUTPUT_DIR=$(abspath $(STAGE1_BIN))
stage2:
	$(MAKE) -C $(BOOTLOADER_SRC)/stage2 stage2 OBJ_DIR=$(abspath $(STAGE2_OBJ)) OUTPUT_DIR=$(abspath $(STAGE2_BIN))
kernel:
	$(MAKE) -C $(KERNEL_SRC) kernel OUTPUT_DIR=$(abspath $(KERNEL_BIN)) OBJ_DIR=$(abspath $(KERNEL_OBJ))
