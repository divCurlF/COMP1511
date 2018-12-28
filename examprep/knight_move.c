//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdio.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

#define BOARD_SIZE 8

struct position {
		int x;
		int y;
};

struct square {
		int count;
};

void print_arr(int arr[BOARD_SIZE*BOARD_SIZE]);
int valid_pos(struct position pos);
void print_result(
				struct square board[BOARD_SIZE][BOARD_SIZE],
				struct position pos
);
int path_length(int arr[BOARD_SIZE*BOARD_SIZE]);
void calc_recurse(
				struct position start_pos,
				struct position end_pos,
				struct square board[BOARD_SIZE][BOARD_SIZE],
				int count,
				int x_inc,
				int y_inc
);

void initialise_board(struct square board[BOARD_SIZE][BOARD_SIZE]);
int convert_char(char c);
char *convert_pos(struct position pos);
void calc_paths(
				struct position start_pos,
				struct position end_pos,
				struct square board[BOARD_SIZE][BOARD_SIZE],
				int count
);

int main(void) {
	struct square board[BOARD_SIZE][BOARD_SIZE];
	initialise_board(board);

	printf("Enter the starting square: ");
	char start_char = getchar();
	int start_second = getchar() - '0' - 1;

	struct position first_pos = {
			.x = convert_char(start_char),
			.y = start_second,
	};

	if (!valid_pos(first_pos)) {
			printf("NOT A VALID SQUARE.\n");
			return 1;
	}

	printf("Enter the ending square: ");
	getchar();
	char end_char = getchar();
	int end_second = getchar() - '0' - 1;

	struct position second_pos = {
			.x = convert_char(end_char),
			.y = end_second,
	};

	if (!valid_pos(second_pos)) {
			printf("NOT A VALID SQUARE.\n");
			return 1;
	}

	int count = 0;
	calc_paths(first_pos, second_pos, board, count);
	print_result(board, second_pos);
	return EXIT_SUCCESS;
}

void print_result(
				struct square board[BOARD_SIZE][BOARD_SIZE],
				struct position pos
) {
		printf("Shortest path is %d\n", board[pos.x][pos.y].count);
}
void initialise_board(struct square board[BOARD_SIZE][BOARD_SIZE]) {
		int y = 0;
		while (y < BOARD_SIZE) {
				int x = 0;
				while ( x < BOARD_SIZE ) {
						board[x][y].count = 0;
						x++;
				}
				y++;
		}
}

void print_board(
				struct square board[BOARD_SIZE][BOARD_SIZE],
				struct position pos
) {
		int y = BOARD_SIZE - 1;
		while ( y >= 0) {
				int x = 0;
				printf("|");
				while ( x < BOARD_SIZE) {
					if ( pos.x == x && pos.y == y) {
							printf("K|");
					} else {
							printf("-|");
					}
					x++;
				}
				printf("\n-----------------\n");
				y--;
		}
}

void calc_paths(
				struct position start_pos,
				struct position end_pos,
				struct square board[BOARD_SIZE][BOARD_SIZE],
				int count
) {

	if (count > 8) {
		//No path takes longer than the size of the board.
		return;
	}

	if (board[start_pos.x][start_pos.y].count >= count ||
		board[start_pos.x][start_pos.y].count == 0) {
		if ((start_pos.x == end_pos.x) && (start_pos.y == end_pos.y)) {
			// TERMINAL We Reach the square
			board[start_pos.x][start_pos.y].count = count;
			return;

		} else {

			count++;
			board[start_pos.x][start_pos.y].count = count;

			calc_recurse(start_pos, end_pos, board, count, 1, 2);
			calc_recurse(start_pos, end_pos, board, count, 2, 1);
			calc_recurse(start_pos, end_pos, board, count, 2, -1);
			calc_recurse(start_pos, end_pos, board, count, 1, -2);
			calc_recurse(start_pos, end_pos, board, count, -1, -2);
			calc_recurse(start_pos, end_pos, board, count, -2, -1);
			calc_recurse(start_pos, end_pos, board, count, -2, 1);
			calc_recurse(start_pos, end_pos, board, count, -1, 2);
		}

	} else {
		// TERMINAL THERE IS ALREADY A SHORTER PATH.
		return;
	}
}

int convert_char(char c) {
		return c - 'a';
}

int valid_pos (struct position pos) {
	return (pos.x >= 0 && pos.x < 8 && pos.y >=0 && pos.y < 8);
}

char *convert_pos(struct position pos) {
		static char pos_string[BOARD_SIZE*BOARD_SIZE];
		pos_string[0] = pos.x + 'a';
		pos_string[1] = pos.y + '1';
		pos_string[2] = '\0';
		return pos_string;
}

void calc_recurse(
				struct position start_pos,
				struct position end_pos,
				struct square board[BOARD_SIZE][BOARD_SIZE],
				int count,
				int x_inc,
				int y_inc
) {
	struct position next_pos = {
			.x = start_pos.x + x_inc,
			.y = start_pos.y + y_inc,
	};

	if (valid_pos(next_pos)) {
		calc_paths(next_pos,end_pos, board, count);
	}
}

int path_length(int arr[BOARD_SIZE*BOARD_SIZE]) {
		int i = 0;
		while (arr[i] != -1) {
				i++;
		}
		return i;
}

void print_arr(int arr[BOARD_SIZE*BOARD_SIZE]) {
		int i = 0;
		printf("Array is: [" );
		printf("%d", arr[i]);
		while ( arr[i] != -1) {
			printf("%d,",arr[i]);
			i++;
		}
		printf("]\n");
}
