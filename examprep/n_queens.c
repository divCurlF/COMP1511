//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

#define EMPTY 0
#define UNAVAIL 1
#define QUEEN 2

struct square {
		int status;
};

int valid_width(int n);
void initialise_board(int n, struct square board[n][n]);
void print_board(int n, struct square board[n][n]);
int solve_queens(int x, int y, int n, struct square board[n][n]);
void place_queen(int x, int y, int n, struct square board[n][n]);

int main(void) {
	int n;
	printf("Enter the size of the board (n > 3): ");
	scanf("%d", &n);
	if (!valid_width(n)) {
			printf("NOT A VALID INPUT\n");
			exit(1);
	}
	struct square board[n][n];
	initialise_board(n, board);
	int x = 0; int y = 0;
	while (y < n) {
		int solved = solve_queens(x, y, n, board);
		if (solved) {
			print_board(n, board);
		} else {
			printf("No Solution Found.\n");
		}
		initialise_board(n,board);
		y++;
	}
	return EXIT_SUCCESS;
}


int solve_queens(int x, int y, int n, struct square board[n][n]) {
		// First Loop through the columns.
		// ITERATE THROUGH COLUMNS
		// If Square empty, place queen, solve next column.
		// Otherwise, go down a row.
		// If y == 8 -> no solution.
		// If x == 8 -> solution found.
		printf("\n");
		print_board(n,board);
		printf("\n");
		int count = 0;

		if (x == n) {
				return TRUE;
		}

		if (count == n) {
				return FALSE;
		}

		if (board[x][y].status == EMPTY) {
				place_queen(x, y, n, board);
				return solve_queens(x+1,y,n,board);
		} else {
				count++;
				return solve_queens(x, (y+1) % n, n, board);
		}
}

void place_queen(int x, int y, int n, struct square board[n][n]) {
		board[x][y].status = QUEEN;
		int i = n-1;
		while (i >= 0) {
				int j = 0;
				while (j < n) {
						//Rows, Cols, Diagonals are covered
						if (!(board[j][i].status == QUEEN)) {
							if (j == x || i == y || abs(x-j) == abs(y-i)) {
									board[j][i].status = UNAVAIL;
							}
						}
						j++;
				}
				i--;
		}
}

int valid_width(int n) {
		return (n > 3);
}

void initialise_board(int n, struct square board[n][n]) {
	int y = n-1;
	while (y >= 0) {
		int x = 0;
		while (x < n) {
			board[x][y].status = EMPTY;
			x++;
		}
		y--;
	}
}

void print_board(int n, struct square board[n][n]) {
		int y = n-1;
		while (y >= 0) {
				int x = 0;
				while (x < n) {
						if (board[x][y].status == EMPTY) {
							printf("-");
						} else if (board[x][y].status == UNAVAIL){
							printf("*");
						} else if (board[x][y].status == QUEEN) {
							printf("Q");
						}
						x++;
				}
				printf("\n");
				y--;
		}

}
