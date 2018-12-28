// COMP1511 Zac Sanchez
// mon09-strings

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NOT_IN_STRING -1
#define BUFFER_LENGTH 4096

int char_index(int c, char *string);
void read_line(int buffer_len, char *buffer);

int main(void) {
	char buffer[BUFFER_LENGTH] = {0};

    // Read in a line...
    printf("Enter a line: ");
    read_line(BUFFER_LENGTH, buffer);

    // Get a character
    printf("Enter a character: ");
    int ch;
    ch = getchar();

    // Find and print character index or "not in string"
    int index = char_index(ch, buffer);
    if (index == NOT_IN_STRING) {
        printf("Character '%c' is not in the string.\n", ch);
    } else {
        printf("Index of character '%c': %d\n", ch, index);
    }
	return 0;
}

int char_index(int c, char *string) {
	int i = 0;
	while (string[i] != c && i < strlen(string)) {
		i++;
	}
	
	if (i == strlen(string)) {
		return NOT_IN_STRING;
	}
	
	return i;
}

void read_line(int buffer_len, char *buffer) {
	char c = getchar();
	int i = 0;
	while (c != '\n' && i < buffer_len) {
		buffer[i] = c;
		c = getchar();
		i++;
	}
	buffer[i] = '\0';
}


