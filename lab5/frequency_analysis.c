//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

#define ALPH_SIZE 26

int main(void) {
	int letter_counts[ALPH_SIZE] = {0};

	int c = getchar();
	double num_chars = 0.0;

	while (c != EOF) {
		if (isalpha(c)) {
			letter_counts[tolower(c) - 'a']++;
			num_chars++;
		}
		c = getchar();
	}
	int i = 0;
	while (i < ALPH_SIZE) {
		double frequency = letter_counts[i] / num_chars;
		printf("'%c' %lf %d \n", i + 'a', frequency, letter_counts[i]);
		i++;
	}

	return EXIT_SUCCESS;
}

