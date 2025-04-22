#ifndef _MODEM_H_
#define _MODEM_H

typedef enum ModemState {
	MODEM_UNKNOWN
};

typedef struct Modem {
	enum ModemState state;
} Modem;

extern void modem_init(Modem*);
extern void modem_send(Modem*, const char *);
#endif
