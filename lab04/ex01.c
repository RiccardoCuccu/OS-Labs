#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main() {

	pid_t pid;
	char command[100];
	char create_log[100];

	while(1) {
		printf("Enter command > ");
		fgets(command, sizeof(command), stdin);
		command[strlen(command) - 1] = '\0';

		if (strcmp(command, "exit") == 0) {
			printf("Goodbye!\n");
			exit(0);
		} else {
			pid = fork();
			if (pid < 0) {
				perror("ERROR during FORK execution: ");
				exit(errno);
			}
			if (pid == 0) {			/* Child process */
				sprintf(create_log, "%s > %d.log", command, getpid());
				system(create_log);
				exit(0);
			}
		}
	}
	return 0;
}
