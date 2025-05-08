#include <assert.h>
#include "james/modem.h"

#define bufSize 128

void hexdump(const char *str) {
	const char *tmp;
	int i;

	for (i=0; i<2; i++) {
		tmp = str;
		printf("> ");
		while(*tmp != 0) {
			if (i == 0) {
				printf("%c  ", *tmp);
			}
			else {
				printf("%0X ", *tmp);
			}
			tmp++;
		}
		printf("\n");
	}
}

void modem_connect() {
	char buf[bufSize];
	int i, numRead;

	for (i=0; i<10; i++) {
	printf("Looking for modem...\n");
	serial_send("ate0\nat\n");
	numRead = serial_getline(buf, bufSize, MODEM_CARRIAGE_RETURN);

	assert(strlen(buf) == numRead);
	if (strcmp(buf, "OK")) {
		printf("Unknown response of %d chars:\n'%s'\n from modem.\n", numRead, buf);
		hexdump(buf);
	}
	else {
		break;
	}
	}
	if (i==5) {
		printf("Timed out\n");
		return;
	}
	printf("Modem ready\n");
}