#ifndef _LOOPBACK_H_
#define _LOOPBACK_H_

/**
 * Send test text and receive text. Designed to be used with physical loopback connector.
 * Stays in a loop until the user interrupts.
 */
extern void loopbackTestLoop(const char *);

#endif /* _LOOPBACK_H_ */