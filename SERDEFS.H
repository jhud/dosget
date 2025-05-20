#ifndef _SERDEFS_H_
#define _SERDEFS_H_

#define PORT1 0x3F8

#define PIC_PORT 0x21 /* Programmable Interrupt Controller */

#define RBR              0    /* Receive buffer register */
#define THR              0    /* Transmit holding reg.   */
#define IER              1    /* Interrupt Enable reg.   */
#define IER_RX_DATA      1    /* Enable RX interrupt bit */
#define IER_THRE         2    /* Enable TX interrupt bit */
#define IIR              2    /* Interrupt ID register   */
#define FCR              2    /* FIFO control register   */
#define IIR_MODEM_STATUS 0    /* Modem stat. interrupt ID*/
#define IIR_TRANSMIT     2    /* Transmit interrupt ID   */
#define IIR_RECEIVE      4    /* Receive interrupt ID    */
#define IIR_LINE_STATUS  6    /* Line stat. interrupt ID */
#define LCR              3    /* Line control register   */
#define LCR_DLAB         0x80 /* Divisor access bit      */
#define LCR_EVEN_PARITY  0x8  /* Set parity 'E' bits     */
#define LCR_ODD_PARITY   0x18 /* Set parity 'O' bits     */
#define LCR_NO_PARITY    0    /* Set parity 'N' bits     */
#define LCR_1_STOP_BIT   0    /* Bits to set 1 stop bit  */
#define LCR_2_STOP_BITS  4    /* Bits to set 2 stop bits */
#define LCR_5_DATA_BITS  0    /* Bits to set 5 data bits */
#define LCR_6_DATA_BITS  1    /* Bits to set 6 data bits */
#define LCR_7_DATA_BITS  2    /* Bits to set 7 data bits */
#define LCR_8_DATA_BITS  3    /* Bits to set 8 data bits */
#define MCR              4    /* Modem control register  */
#define MCR_DTR          1    /* Bit to turn on DTR      */
#define MCR_RTS          2    /* Bit to turn on RTS      */
#define MCR_OUT1         4    /* Bit to turn on OUT1     */
#define MCR_OUT2         8    /* Bit to turn on OUT2     */
#define MCR_LOOPBACK	 0x10 /* Bit for turning on hardware loopback */
#define LSR              5    /* Line Status register    */
#define MSR              6    /* Modem Status register   */
#define DLL              0    /* Divisor latch LSB       */
#define DLM              1    /* Divisor latch MSB       */

#endif /* _MODEM_H_ */
