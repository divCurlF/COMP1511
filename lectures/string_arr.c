//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)

int main(void) {
	char mycity[] = "Great sydney!";
	int size = sizeof(mycity)/sizeof(char);

	int i = 0;
	while (i < size) {
		printf("%c", mycity[i]);
		if (mycity[i] == '\0') {
			printf("\nNull terminator.");
		}
		i++;
	}
	return EXIT_SUCCESS;
}

