#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#define DNASIZE 50000
#define SEQUENCESIZE 30
#define FILENAMESIZE 256

int N, count;
char genome[DNASIZE] = "";
char string[SEQUENCESIZE] = "";
pthread_mutex_t mtx;

struct data {								// Structure with left and right index
	int left;
	int right;
};


void *search(void *args) {
	struct data *p = (struct data*) args;
	int i, j;
	int flag = 0;
	int approx_counter = 0;
	int left = p -> left;
	int right = p -> right;

	for(i = 0; i <= right - left; i++) {				// Loop over the portion of DNA to analyze
		for(j = 0; j < strlen(string); j++) {			// Loop over the pattern inserted by the user

			if (genome[left+i+j] != string[j]) {
				approx_counter++;			// Increase the approximation counter
				if (approx_counter > N) {		// If the number of differences exceeds N it exits the for loop
					approx_counter = 0;
					break;
				}
			}

			if(j == strlen(string) - 1) {			// Match with a degree of approximation <= N
				flag = 1;
			}

		}

		if(flag == 1) {						

			/* Mutex locking */
			pthread_mutex_lock(&mtx);

			count ++;

			/* Mutex unlocking */
			pthread_mutex_unlock(&mtx);
		}

		flag = 0;
	}

	pthread_exit(0);
}

int main(int argc, char *argv[]) {

	int err, i, X, left, right, portion;
	char filename[FILENAMESIZE];
	FILE *f;

	/* Control of the parameters entered */
	if(argc != 5) {
		printf("ERROR: wrong number of parameters!\n");
		printf("Correct syntax example: ./ex.out dna.txt ACT 1 150\n");
		exit(-1);
	}

	/* Control of the length of the pattern */
	if(strlen(argv[2]) > SEQUENCESIZE) {
		printf("ERROR: the pattern must have less than %d bases!\n", SEQUENCESIZE);
		exit(-1);
	}

	strcpy(filename, argv[1]);					// Store the argv[1] value passed by the terminal
	strcpy(string, argv[2]);					// Store the argv[2] value passed by the terminal
	N = atoi(argv[3]);						// Store the argv[3] value passed by the terminal
	X = atoi(argv[4]);						// Store the argv[4] value passed by the terminal

	/* Control of the number of threads */
	if(X <= 0) {
		printf("ERROR: the number of threads must be greater than 0!\n");
		exit(-1);
	}

	//printf("File: %s\n", filename);
	//printf("Pattern: %s\n", string);
	//printf("Approximation: %d\n", N);
	//printf("Threads: %d\n", X);

	count = 0;				
	pthread_t tid[X];						// Array of threads
	struct data leftright[X];					// Array of data structures

	/* Compare the approximation with the number of bases */
	if(strlen(string) <= N) {
		printf("ERROR: the degree of approximation must be lower than the number of bases in the pattern!\n");
		exit(-1);
	}

	/* Mutex initialization */
	if(pthread_mutex_init(&mtx, NULL) != 0) {
		perror("ERROR during PTHREAD_MUTEX_INIT execution");
		exit(errno);
	}

	/* File opening */
	f = fopen(filename, "r");
	if(f == NULL) {
		perror("ERROR during FOPEN execution");
		exit(errno);
	}

	fgets(genome, sizeof(genome), f);
	portion = strlen(genome)/X;					// Number of letters for each thread

	/* Check if the number of threads exceeds the number of DNA elements */
	if(portion == 0) {
		printf("ERROR: the number of threads must be smaller than the number of DNA elements!\n");
		exit(-1);
	}

	left = 0;

	for(i = 0; i < X; i++) {
		if(i == X-1) {
			right = strlen(genome);
		} else {
			right = left + portion -1;
		}
		leftright[i].left = left;				// Left limit
		leftright[i].right = right;				// Right limit

		/* Creation of the threads */
		err = pthread_create(&tid[i], NULL, &search, (void *) &leftright[i]);
		if(err != 0) {
			fprintf(stderr, "ERROR during PTHREAD_CREATE #%d execution: ", i);
			perror("");
			exit(errno);
		}

		left += portion;
	}

	for(i = 0; i < X; i++) {
		/* Waits the threads */
		err = pthread_join(tid[i], NULL);
		if(err != 0) {
			fprintf(stderr, "ERROR during PTHREAD_JOIN #%d execution: ", i);
			perror("");
			exit(errno);
		}
	}

	/* File closing */
	fclose(f);

	/* Mutex destruction */
	if(pthread_mutex_destroy(&mtx) != 0) {
		perror("ERROR during PTHREAD_MUTEX_DESTROY execution");
		exit(errno);
	}

	printf("Number of match: %d\n", count);
	printf("Goodbye!\n");
	
	return 0;
}