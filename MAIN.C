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
	int foo;

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

	serial_listPorts();

	 serial_init(BAUD_300, buf, 1024);

	 while(1){
    	serial_send((foo&1)?"abaracadabra":"zoo");
        foo++;
		serial_receive();
		delay(500);
  	  if (kbhit()) {
          	if (getch() == 27) {
                  printf("User interrupted.\n");
  				break;
  			}
  		}
	}
	serial_shutdown();

	/* Clean up saved args */
	free(url);
	 free(outFilename);
     return 0;
 }
