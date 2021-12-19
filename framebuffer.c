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
    outb(FB_DATA_PORT, pos & 0x00FF);
}

/*
 * fb_write
 * Writes the contents of the buffer buf of length len to the screen
 *
 * @param buf The data to write to the screen
 * @param len The length of the buffer (or how much to write to the screen)
 */
int fb_write(char *buf, unsigned int len) {
    unsigned int cursor_pos = 0;

    for (unsigned int buf_pos = 0; buf_pos < len; buf_pos++) {
        switch (buf[buf_pos]) {
            case '\n':
                cursor_pos = (cursor_pos + FB_WIDTH) - (cursor_pos % FB_WIDTH);
                break;

            default:
                fb_write_cell(2 * cursor_pos, buf[buf_pos], FB_COLOR_LIGHT_GREY, FB_COLOR_BLACK);
                fb_move_cursor(++cursor_pos);
                break;
        }
        
        // Scroll the screen up if necessary
        if (cursor_pos == (FB_WIDTH * FB_HEIGHT)) {
            for (unsigned int i = 0; i < 2 * FB_WIDTH * (FB_HEIGHT - 1); i += 2) {
                fb_write_cell(i, fb[i + (2 * FB_WIDTH)], FB_COLOR_LIGHT_GREY, FB_COLOR_BLACK);
            }

            for (unsigned int i = 2 * FB_WIDTH * (FB_HEIGHT - 1); i < 2 * FB_WIDTH * FB_HEIGHT; i += 2) {
                fb_write_cell(i, 0, FB_COLOR_LIGHT_GREY, FB_COLOR_BLACK);
            }

            cursor_pos = FB_WIDTH * (FB_HEIGHT - 1);
        }
    }

    return len;
}
