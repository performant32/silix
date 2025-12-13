#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define PrintNewLine() write(1, "\n", 1)
struct BPB{
    uint8_t m_Start[3];
    uint8_t m_OEMIdentifier[8];
    uint16_t m_BytesPerSector;
    uint8_t m_BytesPerCluster;
    uint16_t m_ReservedSectors;
    uint8_t m_FatCount;
    uint16_t m_RootEntries;
    uint16_t m_TotalSectors;
    uint8_t m_MediaDescriptorType;
    uint16_t m_SectorsPerFAT;
    uint16_t m_SectorsPerTrack;
    uint16_t m_Heads;
    uint32_t m_HiddenSectors;
    uint32_t m_LargeSectorCount;
    // EBPB
    uint8_t m_DriveNumber;
    uint8_t m_WindowsNTFlags;
    uint32_t m_VolumeId;
    uint8_t m_VolumeLabelString[11];
} __attribute__((packed));

int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr, "bad usage - fat12 filesystem.bin");
        return -1;
    }
    int file = open(argv[1], O_RDONLY);
    if(!file){
        fprintf(stderr, "Failed to open file %s\n", argv[1]);
        return -2;
    }
    printf("Opened fs %s\n", argv[1]);
    off_t size = lseek(file, 0, SEEK_END);
    if(size == -1){
        fprintf(stderr, "Failed to go to end of file\n");
        return -3;
    }
    lseek(file, 0, SEEK_SET);
    char* data = malloc(size);
    struct BPB bpb;
    if(size < 2560){
        fprintf(stderr, "Filesystem is too small, only %u bytes\n", size);
        return -4;
    }
    ssize_t bytesRead = read(file, data, size);
    memcpy(&bpb, data, sizeof(struct BPB));

    write(1, bpb.m_OEMIdentifier, 8);
    PrintNewLine();
    write(1, bpb.m_VolumeLabelString, 11);
    PrintNewLine();

    free(data);
    printf("Closing File");
    close(file);
}
