/* Talk to serial port

Based on: https://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming

IMPORTANT: you must turn server OFF in settings in the 100LX configuration.
Many programs in the 100LX launcher seem to interfere with the serial port
so better to start from DOS to eliminate any interference possibilities.

*/

#include <dos.h>
#include <stdio.h>
#include <conio.h>

#ifdef __TURBOC__
#include "james/defs.h"
#include "james/serial.h"
#else
#include "serial.h"
#endif

#define DB printf

void serial_init(unsigned short int baudId) {
	DB("Starting serial\n");

	if (baudId == 0) {
		printf("Bad baud rate of 0.\n");
		return;
	}

	outportb(PORT1 + 1 , 0); /* Turn off interrupts - Port1 */
	inportb(PORT1); /* Read 1 character so it won't generate an interrupt */

    outportb(PORT1 + LCR , LCR_DLAB); /* SET DLAB ON - bit 7. DLAB specifies upper or lower byte to be edited in 16bit register. High means edit baud rate, low means I/O. */
    outportb(PORT1 + DLL , (char) baudId&0xFF); /* Set Baud rate - Divisor Latch Low Byte */
    outportb(PORT1 + DLM , (char) baudId>>8); /* Set Baud rate - Divisor Latch High Byte */

    outportb(PORT1 + LCR , (LCR_NO_PARITY | LCR_1_STOP_BIT | LCR_8_DATA_BITS)); /* 8 Bits, No Parity, 1 Stop Bit, implicitly clears the DLAB in MSB. */
    outportb(PORT1 + IIR , 0xC7); /* don't know what this is FIFO Control Register */
    outportb(PORT1 + MCR , 0x00); /* Turn off DTR, RTS, and OUT2 */
}

void serial_shutdown() {
	DB("Serial shutdown");
}

void serial_send(const char *str) {
    int c;
    int ch;

	do {
		outportb(PORT1, *str);
		str++;
		/*DB("out:%c\n", *str);*/
	} while (*str != 0);
}

int serial_receive(char *buffer, int bufferLen, bool nullTerminate) {
    int lineStatus;
    int ch;
	int gotCount = 0;
    char foo=20;

	do {
    	serial_send((foo&1)?"a":"z");
		foo++;
		if (gotCount == bufferLen-1) {
			if (nullTerminate) {
				buffer[bufferLen-1] = 0;
			}
			DB("Buffer full\n");
			return gotCount;
		}
  	  lineStatus = inportb(PORT1 + LSR); /* Check to see if char has been received. */
  	  if ((lineStatus & 1) > 0) {
		  ch = inportb(PORT1); /* If so, then get Char */
  		  printf(">%c",ch);

		  *buffer = ch;

		  gotCount++;
		  buffer++;
	  }

	  if ((lineStatus & 2) > 0) {
		  printf("Error: buffer full\n");
	  }

	  if ((lineStatus & 4) > 0) {
		  printf("Error: parity\n");
	  }

	  if ((lineStatus & 8) > 0) {
		  printf("Error: framing\n");
	  }

	  if ((lineStatus & 16) > 0) {
		  printf("SER: break\n");
	  }

	  if ((lineStatus & (32+64)) > 0) {
		  printf("ready: %d\n", lineStatus);
	  }

	  if ((lineStatus & 128) > 0) {
		  printf("Error: bad data\n");
	  }

	  if (kbhit()) {
        	if (getch() == 27) {
                printf("User interrupted.\n");
				break;
			}
		}
	} while (ch != 13 && ch != 10);

	if (nullTerminate) {
		buffer[gotCount] = 0;
	}
	DB("Got %d chars\n", gotCount);
	return gotCount;
}
