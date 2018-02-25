#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGSIZE 16

char * msg1 = "hello, world #1";
char * msg2 = "hello, world #2";
char * msg3 = "hello, world #3";

int main()
{
	char inbuf[MSGSIZE];
	int p[2],j;

	/* open the pipe */
	if(pipe(p) < 0) {
		perror("pipe call");
		exit(1);
	}

	/* write down the pipe*/

	write(p[1], msg1, MSGSIZE);
	write(p[1], msg2, MSGSIZE);
	write(p[1], msg3, MSGSIZE);

	/*read from the pipe*/

	for (j=0; j<3; j++) {
		read (p[0], inbuf, MSGSIZE);
		printf("%s\n", inbuf);
	}

	exit(0);

}


