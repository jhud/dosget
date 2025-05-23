#include <stdio.h>
#include <string.h>
#include "getopt.h"

#include "james/loopback.h"
#include "james/serial.h"



void usage() {
	printf("dosget /u url /o filename.txt [/b 9600 /l /h]\n");
	printf("/b baud rate (default 300)\n");
	printf("/l ignore other params, do loopback test.\n");
	printf("/h loopback with hex dump.\n");
}

int main(int argc, char *argv[]) {
     int opt;
	 char *url = NULL;
	 char *outFilename = NULL;
	char buf[0x7fff];
	int foo;
	uint32_t baud = 300;
	char ch;

	 while((opt = getopt(argc, argv, "lhu:o:b:")) != EOF) {
		switch(opt) {
			case 'l':
			case 'h':
				loopbackTestLoop(opt);
				return 0;
			case 'u':
				url = strdup(optarg);
				break;
			case 'o':
				outFilename = strdup(optarg);
				break;
			case 'b':
				baud = atoi(optarg);
			case '?':
				printf("unknown option\n");
				usage();
				break;
		}
     }
	 if (url == NULL || outFilename == NULL) {

    	usage();
		return -1;
	}

		serial_init(baud, buf, 1024);
	if (!modem_connect()) {
		goto fail_exit;
	}

	modem_get(url, buf, 0x7fff);

fail_exit:
	/* Clean up saved args */
	free(url);
	free(outFilename);
    return 0;
 }
