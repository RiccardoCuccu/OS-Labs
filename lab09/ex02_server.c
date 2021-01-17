#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_NAME "fifo"
#define FIFO_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define FIFO_SIZE 100

int main() {

	int n, rfd;
	char string[FIFO_SIZE];

	/* FIFO creation */
	if(mkfifo(FIFO_NAME, FIFO_MODE) == -1) {
		perror("ERROR during MKFIFO execution");
		exit(errno);
	}

	/* FIFO opening */
	rfd = open(FIFO_NAME, O_RDONLY, 0);
	if(rfd < 0) {
		perror("ERROR during OPEN execution");
		exit(errno);
	}

	/* FIFO reading */
	while(1) {
		n = read(rfd, string, FIFO_SIZE);
		if(n < 0) {
			perror("ERROR during READ execution");
			exit(errno);
		}

		string[n] = '\0';

		if(strcmp(string, "exit") == 0) {
			break;
		}

		if (((strcmp(string, "house") == 0) || (strcmp(string, "casa") == 0))) {
			printf("House detected\n");
		}
	} 

	/* FIFO closing */
	close(rfd);

	/* FIFO unliking */
	unlink(FIFO_NAME);

	/* FIFO delection */
	remove(FIFO_NAME);

	printf("Goodbye!\n");
	return 0;
}
