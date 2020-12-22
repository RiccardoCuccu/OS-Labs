#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	pid_t pid;

	pid = fork();

	if (pid != 0) {
		printf("I'm the father, my PID is %d.\n", getpid());
		pid = fork();
		if (pid != 0) {
			pid =fork();
			if (pid != 0) sleep(1); /* for a correct visualization */
			else printf("I'm the child number 3, my PID is %d. My father PID is %d.\n", getpid(), getppid());
		} else printf("I'm the child number 2, my PID is %d. My father PID is %d.\n", getpid(), getppid());
	} else printf("I'm the child number 1, my PID is %d. My father PID is %d.\n", getpid(), getppid());

	return 0;
}
