#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_VALUE 30
#define ALARM_VALUE 10

int death = -1;

void russian_roulette() {
	/* Re-set signal handler SIGUSR1 */
	signal(SIGUSR1, russian_roulette);
	death = rand() % MAX_VALUE + 1;
	printf("Deadly number: %d\n", death);
}

void send() {
	/* Re-set signal handler SIGALRM */
	signal(SIGALRM, send);
	printf("SIGALRM:> sending SIGUSR1 to father\n");
	alarm(ALARM_VALUE);
	kill(getppid(), SIGUSR1);
}

int main() {

	pid_t pid;
	int r;
	int p[2];

	if(pipe(p) < 0) {
		perror("ERROR during PIPE execution");
		exit(errno);
	}

	pid = fork();
	if (pid < 0) {
		perror("ERROR during FORK execution");
		exit(errno);
	}
	if (pid == 0) {
		/* Process PID as a seed to get a true random number */
		srand(getpid());

		/* Set signal handler SIGALRM */
		signal(SIGALRM, send);
		alarm(ALARM_VALUE);

		while(1) {
			r = rand() % MAX_VALUE + 1;
			write(p[1], &r, sizeof(int));
			sleep(1);
		}
	}

	/* Process PID as a seed to get a true random number */
	srand(getpid());

	/* Set signal handler SIGUSR1 */
	signal(SIGUSR1, russian_roulette);

	while(1) {
		read(p[0], &r, sizeof(int));
		printf("New number received: %d\n", r);
		if(r == death) {
			/* Terminate the child process */
			kill(pid, SIGTERM);
			wait(NULL);
			printf("Child terminated\n");
			break;
		}
	}

	close(p[0]);
	close(p[1]);
	
	printf("Goodbye!\n");
	return 0;
}
