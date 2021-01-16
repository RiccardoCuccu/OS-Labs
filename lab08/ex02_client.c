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

	int msgid, len;
	struct msgbuf Command;

	/* Message queue creation (allocation if already existing) */
	msgid = msgget(getuid(), 0666 | IPC_CREAT);
	if(msgid == -1) {
		perror("ERROR during MSGGET execution");
		exit(errno);
	}

	printf("Message Queue successfully created.\n");

	while(1) {
		printf("Enter command > ");
		fgets(Command.msg_text, MSG_SIZE, stdin);
		len = strlen(Command.msg_text);
		Command.msg_text[len - 1] = '\0';

		/* Message sending */
		if(msgsnd(msgid, &Command, len, 0) == -1){
			perror("ERROR during MSGSND execution");
			exit(errno);
		}

		if(strncmp(Command.msg_text, "exit", 4) == 0){
			break;
		}

		sleep(1);
	}

	printf("Goodbye!\n");

	return 0;
}
