//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdio.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

int wondrous_length(unsigned long num);

int main(void) {
	unsigned long num = 13600000000;
	while (wondrous_length(num) < 1234) {
		if (wondrous_length(num) > 1000) {
			printf("%lu has length %d\n", num, wondrous_length(num));
		}
		num++;
	}
	printf("%lu", num);
	return EXIT_SUCCESS;
}

int wondrous_length(unsigned long num) {
	int count = 1;
	unsigned long i = num;
	while (i != 1) {
		if (i % 2 == 0) {
			i = i/2;
		} else {
			i = 3*i + 1;
		}
		count++;
	}
    return count;
}

