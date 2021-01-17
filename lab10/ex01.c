#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>

int main() {

	pid_t pid;
	int i, j, n;
	int den = 1;
	int p[2];
	double x, ret, sum;

	/* Pipe creation */
	if(pipe(p) < 0) {
		perror("ERROR during PIPE execution");
		exit(errno);
	}

	printf("Enter the base of the series: ");
	scanf("%lf", &x);

	printf("Enter the upper limit of the series: ");
	scanf("%d", &n);

	while(n <= 0) {
		printf("Please enter a positive number: ");
		scanf("%d", &n);
	}

	/* Pipe write */
	for(i = 0; i <= n; i++) {
		pid = fork();
		if (pid < 0) {
			perror("ERROR during FORK execution");
			exit(errno);
		} 
		if (pid == 0) {
			for(j = 1; j <= i; j++) {
				den = den * j;
			}

			ret = pow(x, i) / den;
			write(p[1], &ret, sizeof(double));
			exit(0);
		}
	}

	/* Pipe read */
	for(i = 0; i <= n; i++) {
		read(p[0], &ret, sizeof(double));
		sum += ret;
	}

	close(p[0]);
	close(p[1]);

	printf("Sum: %lf\n", sum);
	printf("Goodbye!\n");
	return 0;
}
