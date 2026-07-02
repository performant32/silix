#ifndef APCI_H
#define APCI_H

#include <stddef.h>
#include <stdint.h>

extern const char* rsdp_checksum;

struct rsdp_t{
    char signature[8];
    uint8_t checksum;
    char oemid[6];
    uint8_t revision;
    uint32_t rsdt_address;
}__attribute__((packed));

void locate_apci_tables();

#endif
