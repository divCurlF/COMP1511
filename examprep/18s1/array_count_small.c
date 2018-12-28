#include <stdio.h>
#include <stdlib.h>


# define TEST_ARRAY_SIZE 9

int count_small(int length, int array[]);

// This is a simple main function which could be used
// to test your count_small function.
// It will not be marked.
// Only your count_small function will be marked.


int main(void) {
    int test_array[TEST_ARRAY_SIZE] = {16, 7, 8, 12, 13, -9, -3, 12, -9};

    int result = count_small(TEST_ARRAY_SIZE, test_array);
    printf("%d\n", result);

    return 0;
}


// return the number of small values in an array.
int count_small(int length, int array[]) {
    int result = 0;
    int i = 0;
    while (i < length) {
    	if (array[i] > -10 && array[i] < 10) {
			result++;
		}
		i++;
    }
    return result;
}
