//COMP1511 Zac Sanchez z5194994
//boxes.c prints out n boxes
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

void print_spiral(int n);
int chebyshev(int x1, int x2, int y1, int y2);
int max(int a, int b);
int isOnLine(int x, int y);
void print_mod_1(int start, int end);
void print_mod_3(int start, int end);
int spiral_length(int n);

void print_num(int n, int x, int y);
int num_looper(int n, int x, int y, int direction);
int spiral_length(int n);
int yMove(int direction, int y);
int xMove(int direction, int x);

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
	int count=0;
	int n = 2*end + 1;
	while (y > start) {
		int x = start + 1;
		while (x < end + 1) {
			if (chebyshev(x, 0, y, 0) % 2 == 0) {
				if (isOnLine(x, y)) {
					count++;
					print_num(n, x, y);
				} else {
					printf("-");
				}
			}
			else {
				if (isOnLine(x,y)) {
					printf("-");
				} else {
					count++;
					print_num(n, x, y);
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
	int count=0;
	int n = 2*end + 1;
	while (y > start) {
		int x = start + 1;
		while (x < end + 1) {
			if (chebyshev(x, 0, y, 0) % 2 == 0) {
				if (isOnLine(x, y)) {
					printf("-");
				} else {
					count++;
					print_num(n,x,y);
				}
			}
			else {
				if (isOnLine(x,y)) {
					count++;
					print_num(n,x,y);
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

//Begin at (0,0) and spiral outwards to current position.

void print_num(int n, int x, int y) {
	//Default value for direction
	int direction = RIGHT;
	//Branch size incremements by two

	//discriminate between each case for each direction.
	if (n % 4 == 3) {
		int result = num_looper(n, x, y, direction);
		printf("%d", result);
	} else {
		direction = LEFT;
		int result = num_looper(n, x, y, direction);
		printf("%d", result);
	}
}

int xMove(int direction, int x) {
	int newx = x;
	if (direction == LEFT) {
		newx--;
	} else if (direction == RIGHT) {
		newx++;
	} else {
		printf("Something went wrong!\n");
	}
	return newx;
}

int yMove(int direction, int y) {
	int newy = y;
	if (direction == DOWN) {
		newy--;
	} else if (direction == UP) {
		newy++;
	} else {
		printf("Something went wrong!\n");
	}
	return newy;
}

int spiral_length(int n) {
	int k = n/2;
	return n + 2*k*(k+1);
}

int num_looper(int n, int x, int y, int direction) {
	int inc = 2;
	//How long the next branch will be
	int branch_len = 2;

	int cur_x = 0;
	int cur_y = 0;

	if (n % 4 == 3) {
		cur_x = -1;
		cur_y = -1;
	}

	int count = 0;

	int length = spiral_length(n);
	int repeat = 2;

	while (length > 0) {
		while (repeat > 0) {
			int cdown = branch_len;
			while (cdown > 0) {
				if (direction == LEFT || direction == RIGHT) {
					cur_x = xMove(direction, cur_x);
					count++;
				} else if (direction == UP || direction == DOWN) {
					cur_y = yMove(direction,cur_y);
					count++;
				} else {
					printf("ERROR.");
				}

				if (cur_x == x && cur_y == y) {
					return count % 10;
				}
				cdown--;
				length--;
			}
			direction = (direction + 1) % 4;
			repeat--;
		}
		repeat = 2;
		branch_len += inc;
	}
	return 0;
}
