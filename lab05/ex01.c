#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

pthread_t tid[2];

void* doThread(void* arg){

	pthread_t id = pthread_self();
	
	if (id == tid[0]) {
		printf("First thread processing\n");
	} else {
		printf("Second thread processing\n");
	}

	sleep(5);

	if(id == tid[0]) {
		printf("First thread terminates\n");
	} else {
		printf("Second thread terminates\n");
	}

	pthread_exit(NULL);
}

int main() {

	int err, i = 0;

	while (i < 2) {
		err = pthread_create(&tid[i], NULL, doThread, NULL);
		if (err != 0) {
			perror("ERROR during thread creation: ");
			exit(errno);
		} else {
			printf("Thread created successfully\n");
		}
		i++;
	}

	i = 0;

	while (i < 2) {
		pthread_join(tid[i], NULL);
		if (i == 0) {
			printf("First thread joined\n");
		} else {
			printf("Second thread joined\n");
		}
		i++;
	}

	return 0;
}