#include <efi.h>
#include <efilib.h>

typedef unsigned int uint32_t;

struct multiboot{
    uint32_t magic;
    uint32_t memLower;
    uint32_t checksum;
};
/*
const uint32_t magicNumber = 0x1BADB002;
const uint32_t flags = 3;
volatile const struct multiboot data __attribute__((section(".multiboot_header"))) = {
    magicNumber,
    flags,
    (uint32_t)(-(flags + magicNumber))
};*/

EFI_STATUS EFIAPI efi_main(EFI_HANDLE imageHandle, EFI_SYSTEM_TABLE* systemTable){
    InitializeLib(imageHandle, systemTable);
    for(;;){
        Print(L"Hello World");
    }
    return EFI_SUCCESS;
}
