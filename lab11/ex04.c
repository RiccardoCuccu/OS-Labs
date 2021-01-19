#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <errno.h>

#define MAX_VALUE 5

double product, x;
pthread_mutex_t mtx;

void *instance(void *arg) {
	double i = *((double *) arg);
	double factor = pow(x, i);

	/* Mutex locking */
	pthread_mutex_lock(&mtx);

	product = product * factor;
	printf("I'm the thread #%.lf, the value of my instance is %lf\n", i, factor);

	/* Mutex unlocking */
	pthread_mutex_unlock(&mtx);

	pthread_exit(NULL);
}

int main() {

	int i, n;

	product = 1;

	/* Mutex initialization */
	if (pthread_mutex_init(&mtx, NULL) != 0) {
		perror("ERROR during PTHREAD_MUTEX_INIT execution");
		exit(errno);
	}

	printf("Enter the base of the series: ");
	scanf("%lf", &x);

	printf("Enter the upper limit of the series: ");
	scanf("%d", &n);

	while(n > MAX_VALUE) {
		printf("Number too high, please enter a number less than or equal to %d: ", MAX_VALUE);
		scanf("%d", &n);
	}

	pthread_t t[n+1];
	double ints[n+1];

	/* Threads generation */
	for(i = 0; i <= n; i++){
		ints[i] = i;
		if (pthread_create(&t[i], NULL, instance, &ints[i]) != 0) {
			printf("ERROR during PTHREAD_CREATE #%d execution: ", i);
			perror("");
			exit(errno);
		}
		/*
		if(pthread_join(t[i], NULL) != 0) {
			printf("ERROR during PTHREAD_JOIN #%d execution: ", i);
			perror("");
			exit(errno);
		}
		*/
	}

	/* Threads waiting */
	for(i = 0; i <= n; i++) {
		if(pthread_join(t[i], NULL) != 0) {
			printf("ERROR during PTHREAD_JOIN #%d execution: ", i);
			perror("");
			exit(errno);
		}
	}

	/* Mutex destruction */
	if (pthread_mutex_destroy(&mtx) != 0) {
		perror("ERROR during PTHREAD_MUTEX_DESTROY execution");
		exit(errno);
	}

	printf("Product: %.lf\n", product);
	printf("Goodbye!\n");

	return 0;
}
