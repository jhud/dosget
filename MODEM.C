/* Talk to modem over serial port

Based on: https://www.edaboard.com/threads/serial-communication-in-turbo-c.197085/

IMPORTANT: you must turn server OFF in settings in the 100LX configuration.
*/

#include <dos.h>
#include <stdio.h>
#include <conio.h>

#ifdef __TURBOC__
#include "james/modem.h"
#else
#include "modem.h"
#endif

#define PORT1 0x3F8

void modem_init(Modem *modem) {
	modem->state = MODEM_UNKNOWN;
	/*modem->buffer = malloc(MODEM_BUFFER_SIZE);*/
	
    outportb(PORT1 + 1 , 0); /* Turn off interrupts - Port1 */

    outportb(PORT1 + 3 , 0x80); /* SET DLAB ON */
    outportb(PORT1 + 0 , 0x0C); /* Set Baud rate - Divisor Latch Low Byte */
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
    outportb(PORT1 + 4 , 0x00); /* Turn off DTR, RTS, and OUT2 */
}

void modem_destroy(Modem *modem) {
	/*free(modem->buffer);
	modem->buffer = NULL;*/
}

void modem_send(Modem *modem, const char *str) {
    int c;
    int ch;

	do {
		outportb(PORT1, *str);
		str++;
	} while (*str != 0);
}

extern int modem_receive(Modem *modem, char *buffer, int bufferLen, BOOL nullTerminate);
    BOOL received;
	int got = 0;
    char ch;

	do {
		if (got == bufferlen-1) {
			if (nullTerminate) {
				buffer[bufferlen-1] = 0;
			}
			return got;
		}
  	  received = inportb(PORT1 + 5) & 1; /* Check to see if char has been received. */
  	  if (received) {
		  ch = inportb(PORT1); /* If so, then get Char */
  		  printf("%c",ch);
		  
		  *buffer = ch;
		  
		  got++;
		  buffer++;
	  }
	} while (received);
	
	if (nullTerminate) {
		buffer[got] = 0;
	}
	return got;
}
