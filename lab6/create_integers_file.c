// read one line from stdin and writes one char per line.
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

	if (argc != 4) {
		fprintf(stderr, "Not enough arguments\n");
		exit(1);
	}

	FILE *out = fopen(argv[3], "w");

	if (out == NULL) {
		fprintf(stderr, "The file cannot be created.");
		exit(1);
	}

	int i = atoi(argv[1]);
	int end = atoi(argv[2]);

	while ( i <= end) {
		fprintf(out, "%d\n", i);
		i++;
	}

	fclose(out);

	return 0;
}
