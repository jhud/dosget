#include "james/loopback.h"
#include "james/serial.h"

void loopbackTestLoop(const char *format) {
	int foo=0;
	char buf[1024];
	char ch;
	printf("Loopback diagnostic test.\nConnect a loopback cable - you should see text appearing.\n");
	serial_listPorts();

	 serial_init(BAUD_300, buf, 1024);

	 while(1){
		serial_send((foo&1)?"at\n":"at\n");
		foo++;
		while(1) {
			ch = serial_getch();
			if (ch) {
			if (format == 'h') {
				printf("%c (0x%X)\t", ch, ch);
				}
				else {
					putch(ch);
				}
			}
			else {
				break;
			}
		}
		delay(250);
  	  if (kbhit()) {
          	if (getch() == 27) {
                  printf("User interrupted.\n");
  				break;
  			}
  		}
	}
	serial_shutdown();
}

