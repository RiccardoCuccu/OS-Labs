#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <errno.h>

#define SHM_SIZE 100

int main() {

	int shmid;
	char command[SHM_SIZE];
	char *shm;
	key_t key=80;

	/* Shared memory creation */
	shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
	if(shmid < 0) {
		perror("ERROR during SHMGET execution: ");
		exit(errno);
	}

	/* Shared memory attachment */
	shm = (char *) shmat(shmid, NULL, 0);
	if(shm == (char *) -1) {
		perror("ERROR during SHMAT execution: ");
		exit(errno);
	}

	/* Shared memory initialization */
	strcpy(shm,"");

	while(1) {
		if(strcmp(shm, "exit") == 0) {
			break;
		}
		system(shm);
		strcpy(command, shm);
		while (strcmp(shm, command) == 0) {};
	}

	/* Shared memory detachment */
	if(shmdt(shm) != 0) {
		perror("ERROR during SHMDT execution: ");
		exit(errno);
	}

	/* Shared memory destruction */
	shmctl(shmid, IPC_RMID, 0);

	printf("Goodbye!\n");

	return 0;
}
