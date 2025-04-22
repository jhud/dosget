#include <stdio.h>
#include <string.h>

#ifdef _DOS
#include “getopt.h”
#include “james/modem.h”
#else
#include "modem.h"
#endif

void usage() {
	printf("dosget /u url /o filename.txt\n");
}

int main(int argc, char *argv[]) {
     int opt;
	 char *url = NULL;
	 char *outFilename = NULL;
	struct Modem modem;

     while((opt = getopt(argc, argv, "u:o:")) != EOF) {
		switch(opt) {
			case 'u':
				url = strdup(optarg);
				break;
			case 'o':
				outFilename = strdup(optarg);
				break;
			case '?':
				printf(“unknown option\n”);
		}
     }
	 if (url == NULL || outFilename == NULL) {

    	usage();
		return -1;
	}
	 printf(url);
	 modem_init(&modem);
    modem_send(&modem, “AT\ntesting testing testing.”);
	free(url);
	 free(outFilename);
     return 0;
 }