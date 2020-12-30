#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define CHILD 3

int main() {
	pid_t pid;
	int i;

	printf("I'm the father, my PID is %d.\n", getpid());
	for(i = 1; i <= CHILD; i++){
		pid = fork();
		if (pid < 0) {
			printf("ERROR during fork() execution!\n");
			exit(-1);
		}
		else if (pid == 0) {
			printf("I'm the child number %d, my PID is %d. My father PID is %d.\n", i, getpid(), getppid());
			exit(0);
		}
	}
	sleep(1);		/* for a correct visualization of the PIDs */

	return 0;
}
