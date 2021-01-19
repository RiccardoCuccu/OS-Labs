#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

int count, n, noprime;
pthread_mutex_t mtx;
pthread_cond_t cond_var;

struct number_segment {
	int left;
	int right;
};

void *searchPrime(void *param){
	struct number_segment *p = (struct number_segment *) param;			// Casting
	int d;
	int i = 0;
	int esc = 0;
	if(p -> left % 2 == 0) i++;							// Increment if even

	while(esc == 0) {

		pthread_mutex_lock(&mtx);
		if (noprime != 0) esc = 1;
		pthread_mutex_unlock(&mtx);

		if(i > p -> right - p -> left) esc = 1;

		d = p -> left + i;
		if(n % d == 0) {							// Not a prime number
			pthread_mutex_lock(&mtx);
			noprime = 1;
			pthread_cond_signal(&cond_var);
			pthread_mutex_unlock(&mtx);
			esc = 1;
		}
		
		i += 2;									// Only odd numbers
	}
	
	pthread_mutex_lock(&mtx);
	if (noprime == 0) {
		count--;
		pthread_cond_signal(&cond_var);
	}
	pthread_mutex_unlock(&mtx);
	pthread_exit(NULL);
}

int main() {

	int i, t;
	int err, left, step;
	//clock_t start, end;

	while(1) {
		printf("Insert the number to test: ");
		scanf("%d", &n);
		if(n < 0) printf("Overflow! The number is too large!\n");
		else if(n != 2 && n % 2 == 0) printf("An even number other than 2 cannot be prime!\n");
		else break;
	}

	//n = 2147483423;								// Prime numbers test
	//n = 99991;

	if(n == 2) {									// Special case
		printf("%d is prime!\n", n);
	} else {
		while(1) {
			printf("Insert the number of threads: ");
			scanf("%d", &t);
			if(t >= n) printf("The number of threads must be less than the number to be tested!\n");
			else break;
		}

		//start = clock();

		count = t;
		noprime = 0;

		step = (n/2)/t;
	
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
				printf("ERROR during PTHREAD_CREATE #%d execution: ", i);
				perror("");
				exit(errno);
			}
	
			left += step;							// Next left limit
		}
	

		pthread_mutex_lock(&mtx);
		while ((noprime == 0) && (count > 0)) pthread_cond_wait(&cond_var, &mtx);
		pthread_mutex_unlock(&mtx);

		/* Threads killing */
		for(i = 0; i < t; i++) {
			pthread_cancel(tid[i]);
		}

		if(noprime == 1) {
			printf("%d is not prime!\n", n);
		} else {
			printf("%d is prime!\n", n);
		}
	}

	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond_var);

	//end = clock();
	//printf("The calculations took %f seconds to run.\n", ((double) (end - start)) / CLOCKS_PER_SEC);
	printf("Goodbye!\n");

	return 0;
}
