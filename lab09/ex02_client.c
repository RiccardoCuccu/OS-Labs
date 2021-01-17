#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_NAME "fifo"
#define FIFO_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main() {

	int wfd;
	char string[100];
	
	/* FIFO opening */
	wfd = open(FIFO_NAME, O_WRONLY, 0);
	if(wfd == -1) {
		perror("ERROR during OPEN execution");
		exit(errno);
	}

	/* FIFO writing */
	while(1) {
		printf("Enter string > ");
		scanf("%s", string);

		if(write(wfd, string, strlen(string)) == -1) {
			perror("ERROR during WRITE execution");
			exit(errno);
		}

		if(strcmp(string, "exit") == 0) {
			break;
		}

	}

	/* FIFO closing */
	close(wfd);

	printf("Goodbye!\n");
	return 0;
}
