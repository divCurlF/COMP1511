// COMP1511 Zac Sanchez
// mon09-strings

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int string_length(char *string);

int main(void) {
	assert(string_length("HELLO WORLD!") == 12);
	return 0;
}

int string_length(char *string) {
	int i = 0;
	while (string[i] != '\0') {
		i++;
	}
	return i;
}


