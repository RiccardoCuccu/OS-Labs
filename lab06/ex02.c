#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

int n;

struct number_segment {
	int left;
	int right;
};

void *searchPrime(void *param){
	struct number_segment *p = (struct number_segment *) param;			// Casting
	int d;
	int i = 0;
	if (p -> left % 2 == 0) i++;
	for(i=i; i < p -> right - p -> left; i += 2) {					// Only odd numbers
		d = p -> left + i;
		if(n % d == 0){								// Not a prime number
			pthread_exit((void *) 1);
		}
	}

	pthread_exit(NULL);
}

int main() {

	int i, t;
	int err, left, noprime, step;
	//clock_t start, end;

	while(1) {
		printf("Insert the number to test: ");
		scanf("%d", &n);
		if (n < 0) printf("Overflow! The number is too large!\n");
		else break;
	}

	//n = 2147483423;								// Prime number test

	if(n == 2) {									// Special case
		printf("%d is prime!\n", n);
	} else {
		printf("Insert the number of threads: ");
		scanf("%d", &t);

		//start = clock();

		step = ((n/2)-2)/t;
	
		pthread_t tid[t];							// Array of threads
		struct number_segment nseg[t];						// Array of data structures
		left = 2;
	
		for(i = 0; i < t; i++){
	
			nseg[i].left = left;						// Left limit
			if(i == t - 1) {
				nseg[i].right = n/2;					// Right limit (last thread)
			} else {
				nseg[i].right = left + step - 1;			// Right limit
			}
	
			/* Creation of the threads */
			err = pthread_create(&tid[i], NULL, &searchPrime, (void *) &nseg[i]);
			if(err != 0) {
				fprintf(stderr, "ERROR while creating the thread %d: ", i);
				perror("");
				exit(errno);
			}
	
			left += step;							// Next left limit
		}
	
		for(i = 0; i < t; i++){

			/* Waits the threads */
			err = pthread_join(tid[i], (void **)&noprime);
			if(err != 0) {
				fprintf(stderr, "ERROR while join the thread %d: ", i);
				perror("");
				exit(errno);
			}
			if (noprime == 1){
				printf("%d is not prime!\n", n);
				printf("Goodbye!\n");
				exit(1);
        		}
		}
	
		printf("%d is prime!\n", n);
	}

	//end = clock();
	//printf("The calculations took %f seconds to run.\n", ((double) (end - start)) / CLOCKS_PER_SEC);
	printf("Goodbye!\n");

	return 0;
}
