#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 1000

int read_input(char buffer[]);
void printEncryption(int shift, int size, char buffer[]);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Requires 2 CLI inputs.\n");
		exit(1);
	}
	
	int arg = atoi(argv[1]);
	
	int shift = ((arg % 26) + 26 ) % 26;
	
	char buffer[MAX_LEN];
	int size = read_input(buffer);
	
	printEncryption(shift, size, buffer);
}

int read_input(char buffer[]) {
	int c = getchar();
	
	int size = 0;
	while (c != EOF) {
		buffer[size] = c;
		size++;
		c = getchar();
	}
	return size;
}

void printEncryption(int shift, int size, char buffer[]) {
	int i = 0;
	while ( i < size ) {
		if (isalpha(buffer[i])) {
			if (islower(buffer[i])) {
				putchar((buffer[i] - 'a' + shift ) % 26 + 'a');
			} else if isupper(buffer[i]) {
				putchar((buffer[i] - 'A' + shift ) % 26 + 'A');
			}
		
		} else {
			putchar(buffer[i]);
		}
		i++;
	}
}
