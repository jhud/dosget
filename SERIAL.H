#ifndef _SERIAL_H_
#define _SERIAL_H_

#ifdef __TURBOC__
#include "james/serdefs.h"
#else
#include "serdefs.h"
#endif

/**
 * Setup serial before use
 */
extern void serial_init();

/**
 * Shutdown serial port, free resources.
 */
extern void serial_shutdown();

/**
 * Send string synchroously
 */
extern void serial_send(const char *);

/**
 * Get a character off serial buffer. 0 if buffer empty.
 * Good for streaming text to output, but not binary.
 */
extern char serial_getch();

/**
 * Poll modem, and fill buffer if bytes are pending.
 * buffer - buffer to fill
 * bufferLen - max buffer size. Will only fill to bufferLen-1 in case there's a null termination.
 * nullTerminate - terminate the buffer with NULL
 * @return num bytes received.
 */
extern int serial_receive(char *, int);

/**
 * Get a full line of output.
 * int newline newline char to terminate line
 * @return num of chars read.
 */
extern int serial_getline(char *, int, char);

/**
 * Debug list all port addresses on machine.
 */
void serial_listPorts();

#endif /* _MODEM_H_ */
