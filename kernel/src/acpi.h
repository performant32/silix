#ifndef ACPI_H
#define ACPI_H

#include <stddef.h>
#include <stdint.h>

typedef struct rsdp_t{
    char signature[8];
    uint8_t checksum;
    char oemid[6];
    uint8_t revision;
    uint32_t rsdt_address;
}__attribute__((packed)) rsdp_t;

typedef struct xsdp_t{
    rsdp_t rsdp;
    uint32_t length;
    uint64_t xsdt_address;
    uint8_t extended_checksum;
    uint8_t reserved[3];
}__attribute__((packed)) xsdp_t;

typedef struct sdt_header_t{
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    char oem_id[6];
    char oem_table_id[8];
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
}__attribute__((packed)) sdt_header_t;

typedef struct rsdt_t{
    sdt_header_t header;
    size_t entries[];
} rsdt_t;

rsdp_t* get_rsdp();

void locate_acpi_tables();
void* locate_acpi_table(char signature[4]);

bool rsdt_verify_checksum(sdt_header_t* header);

extern const char rsdp_checksum[8];
extern const char rsdt_signature[4];
extern rsdp_t* rsdp;
extern rsdt_t* rsdt;

#endif
