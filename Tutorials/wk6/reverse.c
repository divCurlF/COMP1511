//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

#define MAX_LEN 4096

int main(void) {

	char buffer[MAX_LEN];
	int i = 0;
	while (fgets(buffer, MAX_LEN, stdin) != NULL) {
		i = strlen(buffer) - 2;

		while(i >= 0) {
			printf("%c", buffer[i]);
			i--;
		}
		printf("\n");
	}
	return EXIT_SUCCESS;
}

