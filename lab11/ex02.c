#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#define LOOP_LEN 20

sem_t S[2];

void *thread1() {

	for(int i=0; i < LOOP_LEN; i++) {

		/* Semaphore locking or waiting */
		if(sem_wait(&S[0]) == -1) {
			perror("ERROR in thread1() during SEM_WAIT execution");
			exit(errno);
		}

		printf("I'm the thread #1, my TID is %ld\n", pthread_self());
		sleep(1);

		/* Semaphore unlocking */
		if(sem_post(&S[1]) == -1) {
			perror("ERROR in thread1() during SEM_POST execution");
			exit(errno);
		}
	}

	pthread_exit(NULL);
}

void *thread2() {

	for(int i=0; i < LOOP_LEN; i++) {

		/* Semaphore locking or waiting */
		if(sem_wait(&S[1]) == -1) {
			perror("ERROR in thread2() during SEM_WAIT execution");
			exit(errno);
		}

		printf("I'm the thread #2, my TID is %ld\n", pthread_self());
		sleep(1);

		/* Semaphore unlocking */
		if(sem_post(&S[0]) == -1) {
			perror("ERROR in thread2() during SEM_POST execution");
			exit(errno);
		}
	}

	pthread_exit(NULL);
}

int main() {

	int i;
	pthread_t t[2];

	sem_init(&S[0], 0, 1);
	sem_init(&S[1], 0, 0);

	/* Threads generation */
	if (pthread_create(&t[0], NULL, thread1, NULL) != 0) {
		perror("ERROR during PTHREAD_CREATE #1 execution");
		exit(errno);
	}

	if (pthread_create(&t[1], NULL, thread2, NULL) != 0) {
		perror("ERROR during PTHREAD_CREATE #2 execution");
		exit(errno);
	}

	/* Threads waiting */
	for(i = 0; i < 2; i++) {
		if(pthread_join(t[i], NULL) != 0) {
			printf("ERROR during PTHREAD_JOIN #%d execution: ", i);
			perror("");
			exit(errno);
		}
	}

	/* Semaphores destruction */
	if(sem_destroy(&S[0]) == -1) {
			perror("ERROR during SEM_DESTROY #1 execution");
			exit(errno);
	}

	if(sem_destroy(&S[1]) == -1) {
			perror("ERROR during SEM_DESTROY #2 execution");
			exit(errno);
	}

	printf("Goodbye!\n");
	return 0;
}
