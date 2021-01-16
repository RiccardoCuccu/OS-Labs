#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>  
#include <errno.h>

#define FILENAME "number.dat"
#define SHMOBJECT "/shm_object"
#define SHMSIZE 100

int main() {

	int n, shm_fd;
	int tmp;
	void * shm_area;
	pid_t pid;
	FILE *f;

	pid = fork();
	if(pid < 0) {
		perror("ERROR during FORK execution");
		exit(errno);
	}
	if(pid == 0) { /* Child */

		/* POSIX shared memory object creation and opening (opening only if already existing) */
		shm_fd = shm_open(SHMOBJECT, O_RDWR, 0666);
		if(shm_fd == -1) {
			perror("ERROR during SHM_OPEN (child) execution");
			exit(errno);
		}

		/* POSIX shared memory object mapping */
		shm_area = mmap(NULL, SHMSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
		if(shm_area == MAP_FAILED) {
			perror("ERROR during MMAP (child) execution");
			exit(errno);
		}

		do {
			memcpy(&n, shm_area, sizeof(int));		// Copy [sizeof(int)] byte from shm_area to &n
			if(tmp != n && n >= 0) {
				printf("Read number (child): %d\n", n);
				tmp = n;
			}
		} while(n != 0);

		/* POSIX shared memory object unmapping */
		if(munmap(shm_area, SHMSIZE) == -1) {
			perror("ERROR during MUNMAP (child) execution");
			exit(errno);
		}

	} else { /* Parent */

		/* POSIX shared memory object creation and opening (opening only if already existing) */
		shm_fd = shm_open(SHMOBJECT, O_RDWR | O_CREAT, 0666);
		if(shm_fd == -1) {
			perror("ERROR during SHM_OPEN (child) execution");
			exit(errno);
		}

		/* POSIX shared memory object resizing */
		if(ftruncate(shm_fd, SHMSIZE) == -1) {
			perror("ERROR during FTRUNCATE execution");
			exit(errno);
		}

		printf("Shared Memory Region successfully created.\n");

		/* FILENAME opening */
		f = fopen(FILENAME, "r");
		if(f == NULL) {
			perror("ERROR during FOPEN execution");
			exit(errno);
		}

		/* POSIX shared memory object mapping */
		shm_area = mmap(NULL, SHMSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
		if(shm_area == MAP_FAILED) {
			perror("ERROR during MMAP (parent) execution");
			exit(errno);
		}

		do {
			fscanf(f, "%d", &n);
			printf("Read number (parent): %d\n", n);
			memcpy(shm_area, &n, sizeof(int));		// Copy [sizeof(int)] byte from &n to shm_area
			tmp = n;
			sleep(1);
		} while(n != 0);

		fclose(f);

		/* POSIX shared memory object unmapping */
		if(munmap(shm_area, SHMSIZE) == -1) {
			perror("ERROR during MUNMAP (parent) execution");
			exit(errno);
		}

		wait(NULL);

		/* POSIX shared memory object deletion */
		if(shm_unlink(SHMOBJECT) == -1) {
			perror("ERROR during SHM_UNLINK execution");
			exit(errno);
		}

		printf("Shared Memory Region successfully removed.\n");
		printf("Goodbye!\n");
	}
}
