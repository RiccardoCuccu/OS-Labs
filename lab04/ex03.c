#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define N 100
#define RFILE "random.txt"

int main() {
	int i, n;
	pid_t pid;
	char command[100];
	FILE *f;

	/* Process PID as a seed to get a true random number */
	srand(getpid());

	pid=fork();
	if (pid < 0) {
		perror("ERROR during FORK #1 execution: ");
		exit(errno);
	}
	if (pid == 0) {
		f = fopen(RFILE,"w");
		/* Generate 100 random numbers */
		for (i = 0; i < N; i++){
			fprintf(f, "%d ", rand() % 100);
		}
		fclose(f);
		exit(0);
	}

	wait(NULL);
	pid = fork();
	if (pid < 0) {
		perror("ERROR during FORK #2 execution: ");
		exit(errno);
	}
	if (pid == 0) {
		/* Number of byte of the file */
		execl("/usr/bin/wc", "wc", "-m", RFILE, NULL);
	}

	pid = fork();
	if (pid < 0) {
		perror("ERROR during FORK #3 execution: ");
		exit(errno);
	}
	if (pid == 0) {
		/* Number of words of the file */
		execl("/usr/bin/wc", "wc", "-w", RFILE, NULL);
	}

	pid = fork();
	if (pid < 0) {
		perror("ERROR during FORK #4 execution: ");
		exit(errno);
	}
	if (pid == 0) {
		/* Average of all generated number with a custom program */
		execl("./average", "./average", RFILE, NULL);
	}

	while(wait(NULL) > 0){};

	return 0;
}