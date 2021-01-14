#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#define GENOMESIZE 50000
#define SEQUENCESIZE 100
#define FILENAMESIZE  50

char genome[GENOMESIZE] = "";
char sequence[SEQUENCESIZE] = "";

struct genome_segment {
	int first;
	int last;
};

void *runner(void *param){
	int l, i;
	struct genome_segment *p = (struct genome_segment *) param;		// Casting
	l = (p -> last) - (p -> first); 					// Length of the segment to analyze
	for(i = 0; i <= l; i++) {
		if(strncmp(genome + p -> first + i, sequence, strlen(sequence)) == 0) {
			printf("Match found from position %d to position %d.\n", p -> first + i + 1, p -> first + i + (int) strlen(sequence) + 1);
		}
	}
	pthread_exit(NULL);
}

int main() {

	int err, length, i, t;
	char genome_filename[FILENAMESIZE];
	char sequence_filename[FILENAMESIZE];
	//char genome_filename[] = "genome.txt";
	//char sequence_filename[] = "sequence.txt";
	FILE *fgen, *fseq;

	while(1) {
		printf("Insert the genoma filename: ");
		scanf("%s", genome_filename);

		fgen = fopen(genome_filename, "r");				// Open the file with the genome
		if (fgen == NULL) {
			perror("ERROR while opening the genome file");
		} else {
			fscanf(fgen, "%s", genome);
			fclose(fgen);
			break;
		}
	}

	while(1) {
		printf("Insert the sequence filename: ");
		scanf("%s", sequence_filename);
	
		fseq = fopen(sequence_filename, "r");				// Open the file with the sequence to analyze
		if (fseq == NULL) {
			perror("ERROR while opening the sequence file");
		} else {
			fscanf(fseq, "%s", sequence);
			fclose(fseq);
			break;
		}
	}

	while(1) {
		printf("Insert the number of threads: ");
		scanf("%d", &t);
		if(t > strlen(genome) - strlen(sequence)){
			printf("Please enter a number smaller than number of tests.\n");
		} else {
			break;
		}
	}

	pthread_t tid[t];							// Array of threads
	struct genome_segment gseg[t];						// Array of data structures

	length = (strlen(genome) - strlen(sequence))/t;

	for(i = 0; i < t; i++){
		gseg[i].first = i * length;					// Position of the first character
		if(i == t - 1) {
			gseg[i].last = strlen(genome) - strlen(sequence);	// Position of the last character (last thread)
		} else {
			gseg[i].last = i * length + length - 1;			// Position of the last character
		}
		err = pthread_create(&tid[i], NULL, &runner, (void *) &gseg[i]);
		if(err != 0) {
			fprintf(stderr, "ERROR while creating the thread %d", i);
			perror("");
			exit(errno);
		}
	}

	for(i = 0; i < t; i++) {						// Wait all the threads
		err = pthread_join(tid[i], NULL);
		if(err != 0) {
			fprintf(stderr, "ERROR while join the thread %d", i);
			perror("");
			exit(errno);
		}
	}

	printf("Goodbye!\n");

	return 0;
}