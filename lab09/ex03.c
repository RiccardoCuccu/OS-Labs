#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define N 10
#define SLEEP_SEC 10

void sigquit() {
    printf("My dad has killed me... My PID was %d...\n", getpid());
    exit(0);
}

int main() {

	int a, i;
	int counter, flag, killpid, kp;
	pid_t pid[N];

	for(i = 0; i < N; i++) {
		pid[i] = fork();
		if(pid[i] < 0) {
			perror("ERROR during FORK execution");
			exit(errno);
		}

		if(pid[i] == 0) {

			/* Process PID as a seed to get a true random number */
			srand(getpid());
			signal(SIGQUIT, sigquit);

			while(1) {
				a = rand() % SLEEP_SEC+1;
				printf("I'm the child N°%d, my PID is %d, I'll be back active in %d seconds.\n", i+1, getpid(), a);
				sleep(a);
			}
		}
	}

	sleep(1);
	counter = 0;

	while(counter < N) {
		flag = 0;
		printf("Which child do you want me to kill? Choose one of the following PIDs...\n");
		for(i = 0; i < N; i++) {
			if(pid[i] != 0) printf("%d\t", pid[i]);
		}
		printf("\n");
		scanf("%d", &killpid);

		/* Check if the entered PID matches one of the children */
		for(i = 0; i < N; i++) {
			if (pid[i] == killpid) {
				pid[i] = 0;
				flag = 1;
				counter++;
				break;
			}
		}

		/* If the PID matches kill the child */
		if(flag == 1) {
			kp = kill(killpid, SIGQUIT);
			if (kp < 0) {
				perror("ERROR during KILL execution");
				exit(errno);
			}
			waitpid(killpid, NULL, 0);
			printf("Child with the PID %d successfully killed...\n", killpid);
		} else {
			printf("It is not my child.\n");
		}
	}

	printf("I killed all my children as you ordered me...\n");
	printf("Goodbye...\n");
	return 0;
}
