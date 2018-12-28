//COMP1511 Zac Sanchez z5194994
//boxes.c prints out n boxes
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)
void print_spiral(int n);
int chebyshev(int x1, int x2, int y1, int y2);
int max(int a, int b);
int isOnLine(int x, int y);
void print_mod_1(int start, int end);
void print_mod_3(int start, int end);

int main(void) {
	int n;
	printf("Enter size: ");
	scanf("%d", &n);
	print_spiral(n);
	return EXIT_SUCCESS;
}

void print_spiral(int n) {
	//Create cartesian grid with (0,0) as the origin.
	// Remember counting beginning from 0.
	int start = -n / 2 - 1;
	int end = n/2;
	if (n % 4 == 3) {
		print_mod_3(start, end);
	} else {
		print_mod_1(start, end);
	}
}

void print_mod_3(int start, int end) {
	int y = end;
	while (y > start) {
		int x = start + 1;
		while (x < end + 1) {
			if (chebyshev(x, 0, y, 0) % 2 == 0) {
				if (isOnLine(x, y)) {
					printf("#");
				} else {
					printf("-");
				}
			}
			else {
				if (isOnLine(x,y)) {
					printf("-");
				} else {
					printf("#");
				}
			}
			x++;
		}
		printf("\n");
		y--;
	}
}
void print_mod_1(int start, int end) {
	int y = end;
	while (y > start) {
		int x = start + 1;
		while (x < end + 1) {
			if (chebyshev(x, 0, y, 0) % 2 == 0) {
				if (isOnLine(x, y)) {
					printf("-");
				} else {
					printf("#");
				}
			}
			else {
				if (isOnLine(x,y)) {
					printf("#");
				} else {
					printf("-");
				}
			}
			x++;
		}
		printf("\n");
		y--;
	}
}
//This code is almost the same as the box code however anything on the y = - x - 1 diagonal is now switched.
int isOnLine(int x, int y) {
	return (y == -x -1 && y >= 0);
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

