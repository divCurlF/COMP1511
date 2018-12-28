//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)

#define MAX_STR_LEN 200
#define MAX_FINES 1000

struct fines {
	char *name;
	char *reason;
	int fine;
};


int read_fines_file(char filename[], int len, struct fines fines[MAX_FINES]);
void read_fines(FILE *f, struct fines fines[MAX_FINES]);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: student_fine <file_name>\n");
		exit(1);
	}
	struct fines fines[MAX_FINES];
	read_fines_file(argv[1], MAX_FINES, fines);

	return EXIT_SUCCESS;
}

int read_fines_file(char filename[], int len, struct fines fines[MAX_FINES]) {
	FILE *f = fopen(filename, "r");

	if (f == NULL) {
		fprintf(stderr, "File read error.");
		exit(1);
	}

	int i = 0;
	while ( i < len) {
		read_fines(f, fines);
		i++;
	}
	return i;
}

void read_fines(FILE *f, struct fines fines[MAX_FINES]) {
	char first_word[MAX_STR_LEN];
	char second_word[MAX_STR_LEN];;
	// char for_word[4];
	// int fine;
	if (fscanf(f, "%s %s", first_word, second_word) != 2){
		fprintf(stderr, "Incorrect File Format.\n");
	}
	printf("%s %s\n", first_word, second_word);
}

