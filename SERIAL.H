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

extern void serial_shutdown();

/**
 * Send string synchroously
 */
extern void serial_send(const char *);

/**
 * Poll modem, and fill buffer if bytes are pending.
 * buffer - buffer to fill
 * bufferLen - max buffer size. Will only fill to bufferLen-1 in case there's a null termination.
 * nullTerminate - terminate the buffer with NULL
 * @return num bytes received.
 */
extern int serial_receive();

void serial_listPorts();

#endif /* _MODEM_H_ */
