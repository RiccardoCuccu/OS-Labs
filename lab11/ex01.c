#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#define STRING_LEN 256
#define LOOP_LEN 100

sem_t S;
char filename[STRING_LEN];

void *incr3menter() {

	int i, newline, number;
	char c;
	FILE *f;

	for(i = 0; i < LOOP_LEN; i++) {

		newline = -2;

		/* Semaphore locking or waiting */
		if(sem_wait(&S) == -1) {
			perror("ERROR during SEM_WAIT execution");
			exit(errno);
		}
		
		/* Open file for reading and appending*/
		f = fopen(filename, "a+");
		if(f == NULL) {
			perror("ERROR during FOPEN #1 execution");
			exit(errno);
		}

		/* Move file pointer */
		if(fseek(f, -2, SEEK_END) != 0) {
			perror("ERROR during FSEEK #1 execution");
			exit(errno);
		}
	
		/* Find the last newline character */
		while((c = getc(f)) != '\n') {
			newline = newline - 1;
			if(fseek(f, newline, SEEK_END) != 0) {
				perror("ERROR during FSEEK #2 execution");
				exit(errno);
			}
		}
	
		fscanf(f, "%d", &number);
		printf("Number found: %d\n", number);

		number += 3;

		fprintf(f, "%d\n", number);
		fclose(f);
	
		/* Semaphore unlocking */
		if(sem_post(&S) == -1) {
			perror("ERROR during SEM_POST execution");
			exit(errno);
		}

	}

	pthread_exit(NULL);
}

int main() {

	int err, i, n, r;
	FILE *f;

	/* Semaphore initialization */
	sem_init(&S, 0, 1);

	/* Process PID as a seed to get a true random number */
	srand(getpid());

	printf("Specify the name of the file to generate: ");
	scanf("%s", filename);
	strcat(filename, ".txt");

	printf("Specify the number of threads to use: ");
	scanf("%d", &n);

	/* File generating and opening */
	f = fopen(filename, "w");
	if(f == NULL) {
		perror("ERROR during FOPEN execution");
		exit(errno);
	}

	r = rand() % 100;

	fprintf(f, "Number of threads: %d\n", n);
	fprintf(f, "%d\n", r);
	fclose(f);

	printf("File %s generated, initial value entered: %d\n", filename, r);

	pthread_t t[n];

	/* Threads generation */
	for(i = 0; i < n; i++){
		if (pthread_create(&t[i], NULL, incr3menter, NULL) != 0) {
			printf("ERROR during PTHREAD_CREATE #%d execution: ", i);
			perror("");
			exit(errno);
		}
	}

	/* Threads waiting */
	for(i = 0; i < n; i++) {
		err = pthread_join(t[i], NULL);
		if(err != 0) {
			printf("ERROR during PTHREAD_JOIN #%d execution: ", i);
			perror("");
			exit(errno);
		}
	}

	/* Semaphore destruction */
	if(sem_destroy(&S) == -1) {
			perror("ERROR during SEM_DESTROY execution");
			exit(errno);
	}

	printf("Goodbye!\n");
	return 0;
}
