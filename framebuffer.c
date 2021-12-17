#include "framebuffer.h"

// Start address of memory-mapped I/O for framebuffer
char *fb = (char *)0x000B8000;

/*
 * fb_write_cell
 * Writes a character with the given foreground and background to position i
 * in the framebuffer
 *
 * @param i The location in the framebuffer
 * @param c The character to write
 * @param fg The foreground color
 * @param bg The background color
 *
 * Bit:     | 15 | 14 13 12 | 11 10 9 8 | 7 6 5 4 3 2 1 0 |
 * Content: | Nk | BG       | FG        | ASCII           |
 *
 * Nk = Blink bit. If set to 1, text blinks. BG color restricted to colors 0-7
 * for non-blinking text
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    fb[i] = c;
    fb[i + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

/*
 * fb_move_cursor
 * Moves the cursor of the framebuffer to the given position
 *
 * @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (pos >> 8) & 0x00FF);
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF );
}

/*
 * fb_write
 * Writes the contents of the buffer buf of length len to the screen
 *
 * @param buf The data to write to the screen
 * @param length The length of the buffer (or how much to write to the screen)
 */
int fb_write(char *buf, unsigned int length) {
    for (unsigned int i = 0, fb = 0; i < length; i++, fb += 2) {
        fb_move_cursor(i);
        fb_write_cell(fb, buf[i], FB_COLOR_LIGHT_GREY, FB_COLOR_BLACK);
    }

    return length;
}
