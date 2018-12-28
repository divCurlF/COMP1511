//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

#define MAX_LEN 4096

int main(void) {

	FILE *f = fopen("data.txt", "w");

	char buffer[MAX_LEN];

	if (fgets(buffer, MAX_LEN, stdin) != NULL) {
		fputs(buffer, f);
	}
	return EXIT_SUCCESS;
}

