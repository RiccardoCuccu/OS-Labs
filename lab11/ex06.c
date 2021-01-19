#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define T 3

pthread_mutex_t mtx[T];
pthread_cond_t cond_var[T];

struct tdata {
	int i;
};

void *waitForever(void *param) {
	struct tdata *p = (struct tdata *) param;			// Casting
	pthread_cond_wait(&cond_var[(p->i)], &mtx[(p->i)]);;

	printf("Killed TID: %ld\n", pthread_self());
 	pthread_exit(NULL);
}

int main() {

	int err, i;
	int counter, flag, killtid;
	pthread_t tid[T];
	struct tdata td[T];						// Array of data structures

	/* Creation of the threads */
	for(i = 0; i < T; i++) {
		td[i].i = i;
		err = pthread_create(&tid[i], NULL, &waitForever, (void *) &td[i]);
		if(err != 0) {
			printf("ERROR during PTHREAD_CREATE #%d execution: ", i);
			perror("");
			exit(errno);
		}
	}

	counter = 0;

	while(counter < T) {
		flag = 0;
		printf("Which thread do you want me to kill? Choose the corresponding number of one of these TIDs...\n");
		for(i = 0; i < T; i++) {
			if(tid[i] != 0) printf("%d) %ld\t", i, tid[i]);
		}
		printf("\n");
		scanf("%d", &killtid);

		/* Check if the entered TID matches one of the children */
		for(i = 0; i < T; i++) {
			if (i == killtid && tid[i] != 0) {
				flag = 1;
				counter++;
				break;
			}
		}

		/* Send a signal to the entered TID so that it can terminate */
		if(flag == 1) {

			pthread_cond_signal(&cond_var[i]);
			pthread_join(tid[i], NULL);
			pthread_mutex_destroy(&mtx[i]);
			pthread_cond_destroy(&cond_var[i]);
			tid[i] = 0;

		} else printf("It's not one of my threads.\n");
	}

	printf("I killed all my threads as you ordered me...\n");
	printf("Goodbye...\n");
	return 0;
}
