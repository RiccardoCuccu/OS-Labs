#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	char command[100];

	if (argc == 3) {
		sprintf(command, "find %s -name %s", argv[1], argv[2]);
		system(command);
	} else {
		printf("USAGE: find <path> <name>\n");
	}

	return 1;
}