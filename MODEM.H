#ifndef _MODEM_H_
#define _MODEM_H_

#define MODEM_BUFFER_SIZE 2048

typedef enum ModemState {
	MODEM_UNKNOWN
};

typedef struct Modem {
	enum ModemState state;
} Modem;

/**
 * Setup modem before use
 */
extern void modem_init(Modem*);

extern void modem_destroy(Modem*);

/**
 * Send string synchroously
 */
extern void modem_send(Modem*, const char *);

/**
 * Poll modem, and fill buffer if bytes are pending.
 * buffer - buffer to fill
 * bufferLen - max buffer size. Will only fill to bufferLen-1 in case there's a null termination.
 * nullTerminate - terminate the buffer with NULL
 * @return num bytes received.
 */
extern int modem_receive(Modem *, char *, int, BOOL);

#endif /* _MODEM_H_ */
