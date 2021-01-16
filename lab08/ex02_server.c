#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define MSG_SIZE 1024

struct msgbuf {
	long msg_type;
	char msg_text[MSG_SIZE];
};

int main() {

	int msgid;
	char command[MSG_SIZE];
	struct msgbuf Command;

	/* Message queue creation (allocation if already existing) */
	msgid = msgget(getuid(), 0666 | IPC_CREAT);
	if(msgid == -1) {
		perror("ERROR during MSGGET execution");
		exit(errno);
	}

	while(1) {
		/* Message receiving */
		if(msgrcv(msgid, &Command, MSG_SIZE, 0, 0) == -1){
			perror("ERROR during MSGRCV execution");
			exit(errno);
		}

		if(strncmp(Command.msg_text, "exit", 4) == 0){
			break;
		}

		strcpy(command, Command.msg_text);
		system(command);
	}

	printf("Goodbye!\n");

	return 0;
}
