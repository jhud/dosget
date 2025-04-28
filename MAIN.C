#include <stdio.h>
#include <string.h>
#include "getopt.h"

#include "james/serial.h"

void usage() {
	printf("dosget /u url /o filename.txt\n");
}

int main(int argc, char *argv[]) {
     int opt;
	 char *url = NULL;
	 char *outFilename = NULL;
	char buf[1024];

     while((opt = getopt(argc, argv, "u:o:")) != EOF) {
		switch(opt) {
			case 'u':
				url = strdup(optarg);
				break;
			case 'o':
				outFilename = strdup(optarg);
				break;
			case '?':
				printf("unknown option\n");
		}
     }
	 if (url == NULL || outFilename == NULL) {

    	usage();
		return -1;
	}
	 printf(url);
	 serial_init(0x0C);
   /* serial_send("ATds1\n");
sleep(1); */
 serial_receive(buf, 1024, true);
				 printf(buf);
serial_shutdown();

	/* Clean up saved args */
	free(url);
	 free(outFilename);
     return 0;
 }
