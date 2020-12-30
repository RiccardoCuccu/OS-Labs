#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

#define MAX_VALUE 5

int main() {
	pid_t pid;
	int i, n;
	int status;
	int sum = 0;

	printf("Enter the upper limit of the series: ");
	scanf("%d", &n);

	while(n > MAX_VALUE) {
		printf("Number too high, please enter a number less than or equal to %d: ", MAX_VALUE);
		scanf("%d", &n);
	}

	for (i = 0; i <= n; i++) {
		pid = fork();
		if (pid < 0) {
			printf("ERROR during fork() execution!\n");
			exit(-1);
		}
		else if (pid == 0) {
			n = pow(2, i);
			exit(n);		/* it returns the calculated value to the parent process */
		}

	}

	while (pid = wait(&status) > 0){	/* it cycles until there are no more child processes */
		sum += WEXITSTATUS(status);	/* it only adds the STATUS returned by the child processes */
	}

	printf("The sum is %d.\n", sum);

	return 0;
}
