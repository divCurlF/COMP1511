// read one line from stdin and writes one char per line.
// COMP1511 Zac Sanchez z5194994
// Emily Chen m09a
//
//
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 4096

int main(void) {

	char line[MAX_LENGTH];

	printf("Enter a string: ");
	fgets(line, MAX_LENGTH, stdin);
	
	int i = 0;
	while (line[i] != '\n') {
		printf("%c\n", line[i]);
		i++;
	}

	return 0;
}
