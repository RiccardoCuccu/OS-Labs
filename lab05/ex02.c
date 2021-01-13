#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

char string[21] = "";

void* checkstring (void* arg) {
	while (strcmp(string, "exit") != 0) {
		if ((strcmp(string, "house") == 0) || (strcmp(string, "casa") == 0)) {
			printf("House detected\n");
		}
		sleep(1);
	}
	pthread_exit(NULL);
}

int main() {

	int err;
	pthread_t tid;

	err = pthread_create(&tid, NULL, checkstring, NULL);
	if (err != 0) {
		perror("ERROR during thread creation: ");
		exit(errno);
	} else {
		printf("Thread created successfully\n");
	}

	while (strcmp(string, "exit") != 0) {
		printf("Enter string > ");
		scanf("%s", string);
	}

	printf("Goodbye!\n");
	return 0;
}