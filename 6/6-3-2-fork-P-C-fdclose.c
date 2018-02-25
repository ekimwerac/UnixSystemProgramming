#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

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
	printf("Pre-fork: Parent pid <%d>: This pid <%d>\n", (int)getppid(), (int)getpid());

	
	/*fork*/
	int pid=0;
	
	if((pid=fork()) < 0){
		perror("fork call");
		exit(2);
	}

	printf("Post-fork: Parent pid <%d>: This pid <%d>\n", (int)getppid(), (int)getpid());

	/* if parent then close read file
	 * descriptor and write down pipe
	 */
	if(pid>0){
		close(p[0]);
		write(p[1], msg1, MSGSIZE);
		write(p[1], msg2, MSGSIZE);
		write(p[1], msg3, MSGSIZE);
		wait((int *)0);
	}

	/* if child then close write file descriptor 
	 * and read from pipe
	 */
	if(pid == 0){
		close(p[1]);
		printf("Child pid <%d>\n", (int)getpid());
		for (j=0;j<3;j++){
			read(p[0],inbuf, MSGSIZE);
			printf("%s\n", inbuf);
		}
	}
	exit(0);


}


