#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>

#define MAX_VALUE 5

int main() {
	pid_t pid;
	int i, n;
	int shmid;
	long *shm;
	double b, sum;

	printf("Enter the base of the series: ");
	scanf("%lf", &b);

	printf("Enter the upper limit of the series: ");
	scanf("%d", &n);

	while(n > MAX_VALUE) {
		printf("Number too high, please enter a number less than or equal to %d: ", MAX_VALUE);
		scanf("%d", &n);
	}

	/* Shared memory creation */
	shmid = shmget(IPC_PRIVATE, sizeof(double)*n, IPC_CREAT | 0666);
	if(shmid < 0) {
		perror("ERROR during SHMGET execution: ");
		exit(errno);
	}

	/* Shared memory attachment */
	shm = shmat(shmid, NULL, 0);
	if(shm == (void *) -1) {
		perror("ERROR during SHMAT execution: ");
		exit(errno);
	}

	for(i = 0; i < n; i++) {
		pid = fork();
		if (pid < 0) {
			perror("ERROR during FORK execution: ");
			exit(errno);
		} 
		if (pid == 0) {
			shm[i*sizeof(double)] = pow(b, i);
			exit(0);
		}
	}

	sum = 0;
	while(wait(NULL)>0) {}

	for(i = 0; i < n; i++) {
		sum += shm[i*sizeof(double)];
	}
	printf("Sum = %.0lf\n", sum);

	/* Shared memory detachment */
	if(shmdt(shm) != 0) {
		perror("ERROR during SHMDT execution: ");
		exit(errno);
	}

	/* Shared memory destruction */
	shmctl(shmid, IPC_RMID, 0);

	return 0;
}