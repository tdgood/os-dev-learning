#include "serial.h"

/*
 * serial_configure_baud_rate
 * Sets the speed of the data being sent. The default speed of a serial
 * port is 115200 bits/s. The argument is a divisor of that number, hence
 * the resulting speed becomes (115200 / divisor) bits/s.
 *
 * @param com The COM port to configure
 * @param divisor The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

/*
 * serial_configure_line
 * Configures the line of a given serial port. The port is set to have a data
 * length of 8 bits, no parity bits, one stop bit, and break control disabled
 *
 * @param com The COM port
 */
void serial_configure_line(unsigned short com) {
    /*
     * Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * d - enables or disabled DLAB
     * b - enables or disables break control
     * prty - number of parity bits to use
     * s - number of stop bits to use (0 = 1, 1 = 1.5 or 2)
     * dl - length of data
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/*
 * serial_configure_buffers
 * Configures the buffers of a given serial port. The port is set to enable 
 * FIFO, clear both receiver and transmission FIFO queues, and use 14
 * bytes as the size of the queue.
 *
 * @param com The COM port
 */
void serial_configure_buffers(unsigned short com) {
    /*
     * Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
     * Content: | lvl | bs | r | dma | clt | clr | e |
     * lvl - how many bytes should be stored in the FIFO buffers
     * bs - if the buffers should be 16 or 64 bytes large
     * r - reserved
     * dma - how the serial port data should be accessed
     * clt - clear the transmission FIFO buffer
     * clr - clear the receiver FIFO buffer
     * e - if the FIFO buffer should be enabled or not
     */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/*
 * serial_configure_modem
 * Configures the modem of a given serial port. The port is set to have
 * RTS and DTR equal to 1, which means we are ready to send data.
 *
 * @param com The COM port
 */
void serial_configure_modem(unsigned short com) {
    /*
     * Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   | 
     * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
     * r - reserved
     * af - autoflow control enabled
     * lb - loopback mode (used for debugging serial ports)
     * ao2 - auxiliary output 2, used for receiving interrupts
     * ao1 - auxiliary output 1
     * rts - ready to transmit
     * dtr - data terminal ready
     */
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

/*
 * serial_is_transmit_fifo_empty
 * Checks whether the transmit FIFO queue is empty or not for the given
 * COM port
 *
 * @param com The COM port
 * @return 0 if the transmit FIFO queue is not empty
 *         1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned short com) {
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

/*
 * serial_write
 * Writes the contents of buffer buf of length len to the COM1 data port
 *
 * @param buf The data to write
 * @param len The length of the buffer (or how much to write)
 * @return The parameter len
 */
unsigned int serial_write(char *buf, unsigned int len) {
    serial_configure_baud_rate(SERIAL_COM1_BASE, SERIAL_BAUD_RATE_DIVISOR);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_configure_buffers(SERIAL_COM1_BASE);
    serial_configure_modem(SERIAL_COM1_BASE);

    for (unsigned int i = 0; i < len; i++) {
        while (!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE));

        outb(SERIAL_DATA_PORT(SERIAL_COM1_BASE), buf[i]);
    }

    return len;
}
