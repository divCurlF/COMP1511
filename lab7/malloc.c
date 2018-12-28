//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)

struct student {
		char id[20];
		double labs[5];
		double asigns[2];
		char name[100];
};

get_no_lines(char filename[]);

int main(int argc, int *argv[]) {
	int num_lines = get_no_lines(argv[1]);

	//Malloc allocates memeory of requested size. It lives forever until freed. malloc returns pointer to the first address of the block of memory. Returns null if insufficient memory available.
	struct student *sap = malloc( no_lines * sizeof(student));
	
	// always check pointer is not null.
	if (sap == NULL) {
			fprintf(stderr, "Memory Error.")
			return 0;
	}

	// Always free memory after you are done wth it.
	free(p);

	//Makes changes in a function that stay  outside the function.
	int *a = getA();
	printf("%d", a[2]);

	//Free the pointer.
	free(a);
	return EXIT_SUCCESS;
}

// returns pointer
int *getA(void) {

		//creates memory for entire program.
		int *b = malloc(10*sizeof(int));
		b[2] = 55;
		return b;
}

