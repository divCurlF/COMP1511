//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

void read_line(int buffer_len, char *buffer);

int main(void) {
	int size = 100;
	char buffer[size];
	
	read_line(size, buffer);
	printf("%s", buffer);
	return EXIT_SUCCESS;
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

