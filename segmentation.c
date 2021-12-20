#include "segmentation.h"

struct GDTSegmentDescriptor gdt_segment_descriptor[SEGMENTATION_NUM_DESCRIPTORS];

/*
 * segmentation_fill_and_load_gdt
 * Method used to populate our segment descriptors and load our global 
 * descriptor table.
 *
 * Little OS Book didn't cover a lot to figure this out. Most everything
 * involving segmentation was figured out flipping between the Little OS book,
 * https://wiki.osdev.org/GDT, https://wiki.osdev.org/GDT_Tutorial, and Google
 */
void segmentation_fill_and_load_gdt() {
    /*
     * Null descriptor (required)
     */
    gdt_segment_descriptor[0].base1 = 0x0;
    gdt_segment_descriptor[0].flags_limit1 = 0x0;
    gdt_segment_descriptor[0].access_byte = 0x0;
    gdt_segment_descriptor[0].base2 = 0x0;
    gdt_segment_descriptor[0].base3 = 0x0;
    gdt_segment_descriptor[0].limit2 = 0x0;

    /*
     * Kernel code segment
     * Address range 0x00000000 - 0xFFFFFFFF
     * Type - Read/Execute
     * Descriptor Privilege Level - PL0 (kernel mode)
     */
    gdt_segment_descriptor[1].base1 = 0x0;
    gdt_segment_descriptor[1].flags_limit1 = (0x0C << 4) | 0x0F;
    gdt_segment_descriptor[1].access_byte = SEGMENTATION_CODE_ACCESS_BYTE;
    gdt_segment_descriptor[1].base2 = 0x0;
    gdt_segment_descriptor[1].base3 = 0x0;
    gdt_segment_descriptor[1].limit2 = 0xFFFF;

    /*
     * Kernel data segment
     * Address range 0x00000000 - 0xFFFFFFFF
     * Type - Read/Write
     * Descriptor Privilege Level - PL0 (kernel mode)
     */
    gdt_segment_descriptor[2].base1 = 0x0;
    gdt_segment_descriptor[2].flags_limit1 = (0x0C << 4) | 0x0F;
    gdt_segment_descriptor[2].access_byte = SEGMENTATION_DATA_ACCESS_BYTE;
    gdt_segment_descriptor[2].base2 = 0x0;
    gdt_segment_descriptor[2].base3 = 0x0;
    gdt_segment_descriptor[2].limit2 = 0xFFFF;

    // Create struct to hold location of GDT Descriptors
    struct GDT gdt_load = {.size = 0, .address = 0};
    gdt_load.size = (sizeof(struct GDTSegmentDescriptor) * SEGMENTATION_NUM_DESCRIPTORS) - 1;
    gdt_load.address = (unsigned int)&gdt_segment_descriptor;
   
    // Load gdt and segment selection registers
    segmentation_load_gdt(gdt_load);
    segmentation_load_registers();
}
