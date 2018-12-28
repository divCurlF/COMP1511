//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

#define MAX_LEN 4096

int beginsWith(char *string1, char *string2);

int main(void) {

	char string1[MAX_LEN];
	char string2[MAX_LEN];

	while (fgets(string1, MAX_LEN, stdin) != NULL
		&& fgets(string2, MAX_LEN, stdin) != NULL)  {
		if (beginsWith(string1, string2)) {
			printf("%s begins with %s\n", string1, string2);
		} else {
			printf("Nope!\n");
		}
	}
	return EXIT_SUCCESS;
}

int beginsWith(char *string1, char *string2) {
	int i = 0;
	while (string2[i] != '\0' && string2[i] != '\n') {
		if (string1[i] != string2[i]) {
			return FALSE;
		}
		i++;
	}
	return TRUE;
}

