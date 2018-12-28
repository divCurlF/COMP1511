// read one line from stdin and writes one char per line.
// COMP1511 Zac Sanchez z5194994
// Emily Chen m09a
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 4096

int main(void) {

	char line[MAX_LENGTH];
	printf("Enter a string: ");
	fgets(line, MAX_LENGTH, stdin);

	//Subtract one to remove the new line.
	
	int str_size = strlen(line) - 1;
	int i = 0;
	
	// Loop up until str_size / 2, if the characters across array match,
	// it is a palindrome.
	
	while ( i < str_size / 2) {
		if (line[i] != line[str_size-i-1]) {
			printf("String is not a palindrome\n");
			return 0;
		}
		i++;
	}	

	printf("String is a palindrome\n");
	return 0;
}
