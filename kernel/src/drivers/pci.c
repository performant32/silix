#include "pci.h"

#include "acpi.h"
#include "panic.h"
#include "io.h"

void pcie_init(){
    mcfg_acpi_table_t* table = locate_acpi_table("MCFG");
    if(!table || !rsdt_verify_checksum(&table->header)){
        kprintf("Failed to load PCIE MCFG Table\n");
        kpanic();
        return;
    }
    kprintf("Initialized PCIE\n");
}
