#ifndef _MODEM_H_
#define _MODEM_H_

/**
 * All characters which which represent a new line coming from the modem.
 */
#define MODEM_NEWLINES "\x0d\x0a"

extern void modem_connect();

/**
 * Discard all output from the modem, and wait until
 * it stops outputting.
 */
extern void modem_flush();

extern void modem_get(const char * url, char *outBuf, unsigned int bufLen);

#endif _MODEM_H_
