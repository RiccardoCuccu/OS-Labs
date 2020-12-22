#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	pid_t pid;

	pid = fork();

	if (pid < 0) {			/* error case */
		printf("Fork failed");
	} else {
		if (pid == 0) {		/* child process */
			printf("I'm the child, my PID is %d. The father PID is %d.\n", getpid(), getppid());
		} else {		/* fathe process */
			printf("I'm the father, my PID is %d. The child PID is %d.\n", getpid(), pid);
			sleep(1);	/* for a correct visualization */
		}
	}

	return 0;
}