#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <errno.h>

#define MAX_VALUE 10

int main() {

	pid_t pid;
	int i, n;
	int p[2];
	double ret;
	double sum = 0;

	/* Pipe creation */
	if(pipe(p) < 0) {
		perror("ERROR during PIPE execution");
		exit(errno);
	}

	printf("Enter the upper limit of the series: ");
	scanf("%d", &n);

	while(n > MAX_VALUE) {
		printf("Number too high, please enter a number less than or equal to %d: ", MAX_VALUE);
		scanf("%d", &n);
	}

	/* Pipe write */
	for(i = 1; i <= n; i++) {
		pid = fork();
		if (pid < 0) {
			perror("ERROR during FORK execution");
			exit(errno);
		} 
		if (pid == 0) {
			ret = exp(i) / i;
			write(p[1], &ret, sizeof(double));
			exit(0);
		}
	}

	/* Pipe read */
	for(i = 1; i <= n; i++) {
		read(p[0], &ret, sizeof(double));
		sum += ret;
	}

	close(p[0]);
	close(p[1]);

	printf("Sum: %lf\n", sum);
	printf("Goodbye!\n");

	return 0;
}
