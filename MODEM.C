
/* Talk to modem over seial port
Based on:vhttps://www.edaboard.com/threads/serial-communication-in-turbo-c.197085/
*/
#include <stddef.h>

#ifdef _DOS
#include “james/modem.h”
#else
#include "modem.h"
#endif

#define PORT1 0x3F8

#define _COM_INIT 0

#define com1 0
#define settings (0xe0 | 0x03)
void modem_init(Modem *modem) {
	modem->state = MODEM_UNKNOWN;
    outportb(PORT1 + 1 , 0); /* Turn off interrupts - Port1 */

    outportb(PORT1 + 3 , 0x80); /* SET DLAB ON */
    outportb(PORT1 + 0 , 0x03); /* Set Baud rate - Divisor Latch Low Byte */
    /* Default 0x03 = 38,400 BPS */
    /* 0x01 = 115,200 BPS */
    /* 0x02 = 57,600 BPS */
    /* 0x06 = 19,200 BPS */
    /* 0x0C = 9,600 BPS */
    /* 0x18 = 4,800 BPS */
    /* 0x30 = 2,400 BPS */
    outportb(PORT1 + 1 , 0x00); /* Set Baud rate - Divisor Latch High Byte */
    outportb(PORT1 + 3 , 0x03); /* 8 Bits, No Parity, 1 Stop Bit */
    outportb(PORT1 + 2 , 0xC7); /* FIFO Control Register */
    outportb(PORT1 + 4 , 0x0B); /* Turn off DTR, RTS, and OUT2 */
}

void modem_send(Modem *modem, const char *str) {
	while(*str != NULL) {
		bioscom(1, *str, com1);
		printf(“%c”, *str);
		str++;
	}
}
