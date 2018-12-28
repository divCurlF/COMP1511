// prints first 10 lines of a flie 
// COMP1511 Zac Sanchez z5194994
// Emily Chen m09a
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 4096

int main(int argc, char* argv[]) {

	int numlines = 10;

	// Check if there are not enough arguments	
	if (argc != 2 && argc != 4)  {
		fprintf(stderr, "Not enough arguments\n");
		exit(1);
	}
	
	if (strcmp(argv[1],"-n") == 0) {
		numlines = atoi(argv[2]);
	}
	
	//create a buffer.	
	char line[MAX_LENGTH];
	
	// read in the file.
	//
	
	FILE *in;
	
	if (argc == 2) {
		in = fopen(argv[1], "r");
	} else {
		in = fopen(argv[3], "r");
	}

	if (in == NULL) {
		fprintf(stderr, "File read error\n");
		exit(1);
	}

	int i = 0;
	while ((fgets(line, MAX_LENGTH, in) != NULL) && i < numlines) {
		printf("%s", line);
		i++;
	}

	fclose(in);

	return 0;
}
