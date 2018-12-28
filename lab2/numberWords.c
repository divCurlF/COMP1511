//COMP1511 Zac Sanchez
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

int main(void) {
	int number, result;
	printf("Please enter an integer: ");
	result = scanf("%d", &number);

	if (result != 1) {
		printf("ERROR\n");
		exit(1);
	}

	if (number < 1) {
		printf("You entered a number less than one.\n");
	} else if (number == 1) {
		printf("You entered one.\n");
	} else if (number == 2) {
		printf("You entered two.\n");
	} else if (number == 3) {
		printf("You entered three.\n");
	} else if (number == 4) {
		printf("You entered four.\n");
	} else if (number == 5) {
		printf("You entered five.\n");
	} else {
		printf("You entered a number greater than five.\n");
	}

	return EXIT_SUCCESS;
}

