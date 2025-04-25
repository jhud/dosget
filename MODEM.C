/* Talk to modem over serial port
Based on:vhttps://www.edaboard.com/threads/serial-communication-in-turbo-c.197085/

IMPORTANT: you must turn server OFF in settings in the 100LX configuration.*/
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

void modem_send(Modem *modem, const char *str) {
    int c;
    int ch;

printf("\nSample Comm's Program. Press ESC to quit \n");

	do {
	  c = inportb(PORT1 + 5); /* Check to see if char has been */
	  /* received. */
	  if (c & 1) {ch = inportb(PORT1); /* If so, then get Char */
    	printf("%c",ch);} /* Print Char to Screen */

		if (kbhit()){
			ch = getch(); /* If key pressed, get Char */
			outportb(PORT1, ch);
		} /* Send Char to Serial Port */

	} while (ch !=27); /* Quit when ESC (ASC 27) is pressed */
}
