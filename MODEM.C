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

	buf[0] = 0;

	while (1) {
		printf("Looking for modem...\n");
		modem_flush();
		serial_send("ate0\nat\n");
		numRead = 0;
		for (i=0; i<15; i++) {
			numRead = serial_getline(buf, bufSize, MODEM_NEWLINES);

			if (numRead > 0) {
				break;
			}
			delay(200);
			continue;
		}

		assert(strlen(buf) == numRead);
		if (strcmp(buf, "OK")) {
			printf("Unknown response of %d chars:\n'%s'\n from modem.\n", numRead, buf);
			hexdump(buf);
		}
		else {
			break;
		}

	}
	printf("Modem ready\n");
}


void modem_flush() {
	char ch;
	int count;
	count = 0;
	while(1) {
		ch = serial_getch();
		if (!ch) {
			  count++;
			  if (count == 3) {
				return;
			  }
			  delay(50);
		}
		else {
			count = 0;
		}
	}
}


void modem_get(const char * url, char *outBuf, unsigned int bufLen) {
	int count, numRead;

	modem_flush();

	serial_send("atget");
	serial_send(url);
	serial_send("\n");

	while(1) {
		numRead = serial_getline(outBuf, bufLen, "");
		if (numRead == 0) {
			/* Buffer is empty. Wait for response.*/
			delay(1000);
			count++;
			if (count == 5) {
				break;
			}
		}
		else {
			count = 0;
			printf(outBuf);
		}
	}
	printf("Done\n");
}
