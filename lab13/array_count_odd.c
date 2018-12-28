#include <stdio.h>
#include <stdlib.h>


# define TEST_ARRAY_SIZE 8

int count_odd(int length, int array[]);

// This is a simple main function which could be used
// to test your count_odd function.
// It will not be marked.
// Only your count_odd function will be marked.


int main(void) {
    int test_array[TEST_ARRAY_SIZE] = {16, 7, 8, 12, 13, 19, 21, 12};

    int result = count_odd(TEST_ARRAY_SIZE, test_array);
    printf("%d\n", result);

    return 0;
}


// return the number of odd values in an array.
int count_odd(int length, int array[]) {
	int count = 0;
	int i = 0;
	while ( i < length ) {
		if (array[i] % 2 != 0) {
			count++;
		}
		i++;
	}
    return count;
}
