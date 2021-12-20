#ifndef SEGMENTATION_H
#define SEGMENTATION_H

// Segmentation sizes and types
#define SEGMENTATION_NUM_DESCRIPTORS 3
#define SEGMENTATION_CODE_ACCESS_BYTE 0x9A
#define SEGMENTATION_DATA_ACCESS_BYTE 0x92

// Struct to hold starting address and size of GDT
struct GDT {
    unsigned short size;
    unsigned int address;
} __attribute__((packed));

// Struct to hold descriptor data
// Found on https://wiki.osdev.org/GDT
struct GDTSegmentDescriptor {
    unsigned short limit2;
    unsigned short base3;
    unsigned char base2;
    unsigned char access_byte;
    unsigned char flags_limit1;
    unsigned char base1;
} __attribute__((packed));

void segmentation_fill_and_load_gdt();

void segmentation_load_gdt(struct GDT gdt);
void segmentation_load_registers();

#endif
