/* O_NDELAY example */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define MSGSIZE 6

char * msg1 = "Hello";
char * msg2 = "Bye";
void child(int *);
void parent(int *);

void fatal(char * s)
{
	perror(s);
	exit(1);
}

int main()
{
	int pfd[2];

	/* Open the pipe */
	if ((pipe(pfd))< 0) {
		fatal("pipe call: ");
	}

	/*set O_NDELAY flag for p[0] */
	if(fcntl(pfd[0], F_SETFL, O_NDELAY) < 0 ){
		fatal("fcntl call");
	}

	switch (fork()){
		case -1:	/* error */
			fatal("fork call: ");
		case 0: 	/* Child */
			child(pfd);
		default:	/* Parent */
			parent(pfd);
	}

}

void parent(p)  /* Code for parent */
int p[2];
{
	int nread;

	char buf[MSGSIZE];

	close(p[1]);
	sleep(9);

	for(;;) {
		switch(nread = read(p[0], buf, MSGSIZE)){
			case -1:
				fatal("read call oops: ");
			case 0:
				printf("(pipe empty)\n");
				sleep(1);
				break;
			default:
				if(strcmp(buf,msg2) == 0){
					printf("End of Conversation\n");
					exit(0);
				} else {
					printf("MSG=%s\n", buf);
				}
		}
	}
}

void child(p)
int p[2];
{
	int count;
	close(p[0]);
	sleep(9);
	for(count=0; count < 3; count++) {
		write(p[1], msg1, MSGSIZE);
		sleep(3);
	}

	/* send final message */
	write(p[1],msg2, MSGSIZE);
	exit(0);
}


