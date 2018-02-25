/* Write down a pipe until we get a blockage */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#include <signal.h>

int count;
int alrm_action();

int main()
{
	int p[2];
	char c='x';

	if(pipe(p) < 0){
		perror("pipe call");
		exit(1);
	}

	signal(SIGALRM, alrm_action);

	for (count=0;;){
		/* set alarm */
		alarm(20);
		/* Write down the pipe */
		write(p[1],&c,1);;
		/* Reset alarm */
		alarm(0);

		if((++count % 1024) == 0){
			printf("%d characters in pipe\n", count);
		}
	}
}

/* Called when SIGALARM received*/
alrm_action(){
	printf("write blocked after %d characters\n", count);
	exit(0);
}


