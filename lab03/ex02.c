#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define CHILD_INFINITE 3
#define CHILD_FINITE 3
#define RANDOM_NUMBERS 3

void child_infinite(int i) {
	int j = 1;
	srand(getpid());		/* it use the process pid as a seed to get a true random number */
	printf("I'm the child number %d, I will generate random numbers forever.\n", i);
	sleep(1);			/* for a correct visualization */
	while(1) {
		printf("CHILD %d \t CYCLE %d \t NUMBER %d \n", i, j, rand()%100);
		sleep(3);		/* to reduce the printing frequency */
		j++;
	}
}

void child_finite(int i) {
	int j, n;
	srand(getpid());		/* it use the process pid as a seed to get a true random number */
	printf("I'm the child number %d, I will generate %d random numbers and their squares.\n", i+CHILD_INFINITE, RANDOM_NUMBERS);
	sleep(1);			/* for a correct visualization */
	for (j = 1; j <= RANDOM_NUMBERS; j++){
		n = rand()%100;
		printf("CHILD %d \t CYCLE %d \t NUMBER %d \t SQUARE %d \n", i+CHILD_INFINITE, j, n, n*n);
		sleep(3);		/* to reduce the printing frequency */
	}
	exit(0);
}

int main (){
	pid_t pid;
	int i;
	int status;

	for (i = 1; i <= CHILD_INFINITE; i++){
		pid = fork();
		if (pid < 0) {
			printf("ERROR during fork() execution!\n");
			exit(-1);
		}
		else if (pid == 0) {
			child_infinite(i);
		}
	}

	for (i = 1; i <= CHILD_FINITE; i++){
		pid = fork();
		if (pid < 0) {
			printf("ERROR during fork() execution!\n");
			exit(-1);
		}
		else if (pid == 0) {
			child_finite(i);
		}
	}

	i--;
	while(1){
		pid = wait(NULL);	/* wait for a child */
		if (pid >= 0) {
			i++;
			pid = fork();
			if (pid < 0) {
				printf("ERROR during fork() execution!\n");
				exit(-1);
			}
			else if (pid == 0) {
				child_finite(i);
			}
		}
		else {
			printf("ERROR in the returned value by the child process!\n");
			return -1;
		}
	}

	return 0;
}
