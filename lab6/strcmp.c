// COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE (!FALSE)

#define MAX_LINE_LENGTH 4096

int myStrCmp(char *string1, char *string2);
int myStrLen(char *string1);

int main(void) {
	char string1[MAX_LINE_LENGTH] = "abcdef";
	char string2[MAX_LINE_LENGTH] = "abcde";
	printf("String1 is %d long\n", myStrLen(string1));
	printf("String1 is %d long\n", myStrLen(string2));
	printf("Comparing strings %s %s... %d\n", string1, string2,
		   myStrCmp(string1, string2)
		  );
	return EXIT_SUCCESS;
}

int myStrCmp(char *string1, char *string2) {
	int i = 0;
	int same = 0;
	while (string1[i] == string2[i]) {
		same = 1;
		i++;
	}
	return 0;
}

int myStrLen(char *string) {
		int i = 0;
		while (string[i] != '\0') {
			i++;
		}
		return i;
}

int isSubstring(char *string1, char *string2) {
		int i = 0;
		int sub = 0;
		while (string1[i] != '\0') {
			if (string1[i] == string2[i]) {
					sub = 1;
			} else {
					sub = 0;
			}
			i++;
		}
		return sub;
}
