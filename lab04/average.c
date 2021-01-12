#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <time.h>
//#include <sys/types.h>
//#include <sys/wait.h>
#include <errno.h>

int main (int argc, char* argv[]) {

	int i, j;
	int average;
	int numbers[100];
	char command[100];
	
	FILE *f;

	i=0;
	average=0;

	if (argc == 2) {
		f=fopen(argv[1], "r");

		if (f == NULL) {
			perror("ERROR during FOPEN execution: ");
			exit(errno);
		}

		while (fscanf(f, "%d", &numbers[i]) == 1) {
			average += numbers[i];
			i++;
		}

		printf("The average is %d\n", average/i);
		exit (0);
	} else {
		printf("USAGE: ./average <path>\n");
	}

	return 0;
}