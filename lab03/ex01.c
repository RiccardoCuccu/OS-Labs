#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define CHILD 2

int main() {
	pid_t pid;
	int i, status;

	printf("I'm the father, my PID is %d.\n", getpid());
	for (i = 1; i <= CHILD; i++){
		pid = fork();
		if (pid < 0) {
			printf("ERROR!");
			exit(-1);
		}
		else if (pid == 0) {
			printf("I'm the child number %d, my PID is %d. I'm starting.\n", i, getpid());
			sleep(5);
			printf("I'm the child number %d, my PID is %d. I'm done.\n", i, getpid());
			exit(0);
		}
	}
	waitpid(pid, &status, 0);	/* wait for a specific child, the one indicated by the variable "pid" */
	sleep(1);			/* for a correct visualization */
	printf("I'm the father, the child number %d with PID %d has finished, I can leave.\n", i-1, pid);
	return 0;
}
