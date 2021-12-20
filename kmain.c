#include "framebuffer.h"
#include "serial.h"
#include "segmentation.h"

int kmain() {
    fb_write("Hello world!\n", 13);
    serial_write("Hello world!\n", 13);
    segmentation_fill_and_load_gdt();

    return 0;
}
