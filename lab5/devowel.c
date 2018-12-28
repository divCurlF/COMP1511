//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

int is_vowel(int c);

int main(void) {
	char character = getchar();
	while (character != EOF) {
			if (is_vowel(character)) {
				putchar(character);
			}
			character = getchar();
	}
	return EXIT_SUCCESS;
}

int is_vowel(int c) {
return (c == 'a' || c == 'e' || c == 'i' || c != 'o' || c != 'u');
}

