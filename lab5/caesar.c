//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

int caesar_shift(char c, int shift);

int main(int argc, char *argv[]) {
	int cmd = atoi(argv[1]);
	char character = getchar();
	while (character != EOF) {
			putchar(caesar_shift(character, cmd));
			character = getchar();
	}
	return EXIT_SUCCESS;
}

int caesar_shift(char c, int shift) {
	int new_index = 0;
	if (islower(c)) {
		int index = c - 'a';
		new_index = (index + shift) % 26;
		return new_index + 'a';
	} else if (isupper(c)) {
		int index = c - 'A';
		new_index = (index + shift) % 26;
		return new_index + 'A';
	}
	return c;
}

