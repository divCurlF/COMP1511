#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 4096

int isPalindrome(char *buffer);

int main(void) {
	printf("Enter a string: ");
	char buffer[MAX_LEN];
	
	if (fgets(buffer, MAX_LEN, stdin) == NULL) {
		fprintf(stderr, "Error reading string.");
	}
	
	char *newline = strchr(buffer, '\n');
	newline[0] = '\0';
	
	if (isPalindrome(buffer)) {
		printf("String is a palindrome\n");
	} else {
		printf("String is not a palindrome\n");
	}
}

int isPalindrome(char *buffer) {
	char clean_string[MAX_LEN];
	int clean_curr = 0;
	int i = 0;
	while (buffer[i] != '\0') {
		if (isalpha(buffer[i])) {
			clean_string[clean_curr] = tolower(buffer[i]);
			clean_curr++;
		}
		i++;
	}
	clean_string[clean_curr] = '\0';
	
	i = 0;
	while (i < clean_curr) {
		if (clean_string[i] != clean_string[clean_curr-1-i]) {
			return 0;
		}
		i++;
	}
	return 1;
}
