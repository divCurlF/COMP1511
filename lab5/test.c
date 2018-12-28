//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)

int main(int argc, char * argv[]) {
	int diff = (argv[2][0] - argv[1][0]) % 26;
	printf("diff is %d\n", diff);
	return EXIT_SUCCESS;
}

