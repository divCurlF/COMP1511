//COMP1511 Zac Sanchez z5194994
//boxes.c prints out n boxes
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)
void print_boxes(int n);
int chebyshev(int x1, int x2, int y1, int y2);
int max(int a, int b);

int main(void) {
	int n;
	printf("How many boxes: ");
	scanf("%d", &n);
	print_boxes(n);
	return EXIT_SUCCESS;
}

void print_boxes(int n) {
	//Create cartesian grid with (0,0) as the origin.
	// Remember counting beginning from 0.
	int start = (1 - 2*n);
	int end = (2*n);
	int i = start;
	while (i < end) {
		int j = start;
		while (j < end) {
			if (chebyshev(j, 0, i, 0) % 2 == 1) {
				printf("#");
			}
			else {
				printf(" ");
			}
			j++;
		}
		printf("\n");
		i++;
	}
}

//CREDIT: https://en.wikipedia.org/wiki/Chebychev_distance
int chebyshev(int x1, int x2, int y1, int y2) {
	return max(abs(x1 - x2), abs(y1 - y2));
}

int max(int a, int b) {
	 if (a >= b) {
		 return a;
	 } else {
		 return b;
	 }
 }
