// read one line from stdin and writes one char per line.
// COMP1511 Zac Sanchez z5194994
// Emily Chen m09a
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 4096

int main(void) {

	char line[MAX_LENGTH];
	printf("Enter a string: ");
	fgets(line, MAX_LENGTH, stdin);

	char cleanLine[MAX_LENGTH];

	int i = 0;
	int cleanLineCursor = 0;
	while (line[i] != '\0') {
		if (isalpha(line[i])) {
			cleanLine[cleanLineCursor] = tolower(line[i]);
			cleanLineCursor++;
		}
		i++;
	}

	cleanLine[cleanLineCursor] = '\0';

	//Subtract one to remove the new line.

	int str_size = strlen(cleanLine);

	// Loop up until str_size / 2, if the characters across array match,
	// it is a palindrome.

	i = 0;
	while ( i < str_size / 2) {
		if (cleanLine[i] != cleanLine[str_size-i-1]) {
			printf("String is not a palindrome\n");
			return 0;
		}
		i++;
	}

	printf("String is a palindrome\n");
	return 0;
}
