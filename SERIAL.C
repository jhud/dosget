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

#define INTVECT 0x0c /* int 0C irq4 com1 interrupt */

#define DB printf

char * g_buffer;
int g_bufferIn;
int g_bufferOut;
int g_bufferSize;
void interrupt (*g_oldISR)();

static void interrupt PORT1INT() /* Interrupt Service Routine (ISR) for PORT1 */
{
	int c;
    c = inportb(PORT1 + LSR);
    if (c & 1) {
        g_buffer[g_bufferIn] = inportb(PORT1);
        g_bufferIn++;
        g_bufferIn %= g_bufferSize;
    }
		if (c & 2) {
/*        	outportb(PORT1, 64 + rand()%26);*/
		}
/*enable();       */
    outportb(0x20, 0x20);
}

void serial_init(unsigned short int baudId, char *buffer, int bufferSize) {
	int baudMSB = baudId >> 8;
	int baudLSB = baudId & 0xFF;

	DB("Starting serial\n");

	if (baudId == 0) {
		printf("Bad baud rate of 0.\n");
		return;
	}

	if (g_buffer) {
		printf("Serial already started.\n");
		return;
	}

	g_buffer = buffer;
	g_bufferSize = bufferSize;

	outportb(PORT1 + IER , 0); /* Turn off all interrupts - Port1 */
	/* inportb(PORT1); Read 1 character so it won't generate an interrupt */
	g_oldISR = getvect(INTVECT); /* Save old Interrupt Vector for later recovery */
    setvect(INTVECT, PORT1INT); /* Set Interrupt Vector Entry */

    outportb(PORT1 + LCR , LCR_DLAB); /* SET DLAB ON - bit 7. DLAB specifies upper or lower byte to be edited in 16bit register. High means edit baud rate, low means I/O. */
    outportb(PORT1 + DLL , (unsigned char) baudLSB); /* Set Baud rate - Divisor Latch Low Byte */
    outportb(PORT1 + DLM , (unsigned char) baudMSB); /* Set Baud rate - Divisor Latch High Byte */

    outportb(PORT1 + LCR , (LCR_NO_PARITY | LCR_1_STOP_BIT | LCR_8_DATA_BITS)); /* 8 Bits, No Parity, 1 Stop Bit, implicitly clears the DLAB in MSB. */
    outportb(PORT1 + FCR , 0x7); /* 0 - no fifo for testing. 7 trigger on 1 byte. 0xC7 - trigger on 14 bytes); FIFO Control Register */
    outportb(PORT1 + MCR , 0x00); /* Turn off DTR, RTS, and OUT2 */

	disable();
	outportb(PIC_PORT, (inportb(PIC_PORT) & 0xEF)); /* enable irq4 com1. Low is active. */
/*    outportb(0x20, 0xc39);*/
	enable();

	outportb(PORT1 + MCR, MCR_OUT2); /* out2 bit enables interrupts */
	outportb(PORT1 + IER, IER_RX_DATA); /* Bit 0 - interrupt when data received on LSR. Bit 1, transmitter buffer is empty. */
}

void serial_listPorts() {
    unsigned int far *ptraddr;  /* Pointer to location of Port Addresses */
    unsigned int address;       /* Address of Port */
    int a;

    ptraddr=(unsigned int far *)0x00000400;

    for (a = 0; a <  4; a++)
      {
       address = *ptraddr;
       if (address == 0)
                   printf("No port found for COM%d \n",a+1);
       else
                   printf("Address assigned to COM%d is %Xh\n",a+1,address);
       *ptraddr++;
      }
}

void serial_shutdown() {
	DB("Serial shutdown");
	outportb(PORT1 + 1, 0); /* Turn off interrupts - Port1  */
	outportb(PIC_PORT, (inportb(PIC_PORT) | 0x10)); /* MASK IRQ using PIC */
	setvect(INTVECT, g_oldISR);
}

void serial_send(const char *str) {
	do {
		outportb(PORT1, *str);
		delay(100);
		str++;
	} while (*str != 0);
}

int serial_receive() {
    int lineStatus;
    int ch;
	int gotCount = 0;

		while (g_bufferIn != g_bufferOut) {
            ch = g_buffer[g_bufferOut];
            g_bufferOut++;
			g_bufferOut %= g_bufferSize;
			gotCount++;
			printf("%c", ch);
		}

  	  lineStatus = inportb(PORT1 + LSR); /* Check to see if char has been received.*/
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

	/*  if ((lineStatus & (32+64)) > 0) {
		  printf("ready: %d\n", lineStatus);
	  } */

	  if ((lineStatus & 128) > 0) {
		  printf("Error: bad data\n");
	  }

	DB("Got %d chars\n", gotCount);
	return gotCount;
}
