//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)

int main(void) {
	int num;
	int nums[10000];
	int i = 0;
	while (scanf("%d", &num) == 1) {
		nums[i] = num;
		i++;
	}

	printf("%d\n", nums[i/2]);
	return EXIT_SUCCESS;
}

