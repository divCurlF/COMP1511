//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)
int sum(int a[], int size);
int max(int a[], int size);

int main(void) {
	int a[5] = {1,23,4,5,1};
	int size = sizeof(a)/sizeof(int);

	int arr_sum = sum(a, size);
	int arr_max = max(a, size);

	printf("Sum is %d Max is %d\n",arr_sum, arr_max);

	return EXIT_SUCCESS;
}

int sum(int a[], int size) {
	int sum = 0;
	int i = 0;
	while(i < size) {
		sum += a[i];
		i++;
	}
	return sum;
}

int max(int a[], int size) {
	int max = a[0];
	int i = 0;

	while (i < size) {
		if (a[i] > max) {
			max = a[i];
		}
		i++;
	}
	return max;
}

