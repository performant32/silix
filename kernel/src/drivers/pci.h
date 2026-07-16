#ifndef PCH_H
#define PCH_H

#include "acpi.h"

typedef struct mcfg_entry_t{
    uint64_t base_address;
    uint16_t pci_segment_group_number;
    uint8_t start_pci_number;
    uint8_t end_pci_number;
    uint32_t reserved;
}__attribute__((packed)) mcfg_entry_t;

typedef struct mcfg_acpi_table_t{
    sdt_header_t header;
    uint64_t reserved;
    mcfg_entry_t entries[];
}__attribute__((packed)) mcfg_acpi_table_t;
void pcie_init();
#endif
