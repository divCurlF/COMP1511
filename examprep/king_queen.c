//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

#define BOARD_LEN 8

typedef enum {
	EMPTY,
	KING,
	QUEEN,
} Piece;

typedef struct _square {
	int x;
	int y;
	Piece piece;
} Square;

int queenAttacksKing(Square king_square, Square queen_square);
void insertSquare(Square square, Square chessboard[BOARD_LEN][BOARD_LEN]);
void createBoard(Square chessboard[BOARD_LEN][BOARD_LEN], Square k, Square q);
void printChessboard(Square chessboard[BOARD_LEN][BOARD_LEN], int x, int y);
int alternativeTest(Square k, Square q);

int main(void) {
	printf("Enter the king pos: ");
	char c;
	int d;
	scanf("%c%d", &c, &d);
	int x1 = tolower(c) - 'a';
	int y1 = d;
	getchar();
	printf("Enter the queen pos: ");
	scanf("%c%d", &c, &d);

	int x2 = tolower(c) - 'a';
	int y2 = d;

	Square king = {x1, y1, KING};
	Square queen = {x2, y2, QUEEN};

	if (queenAttacksKing(king, queen)) {
		printf("King is under attack!\n");
	} else {
		printf("King is safe.\n");
	}

	if (alternativeTest(king, queen)) {
		printf("Simple yes.\n");
	} else {
		printf("Simple no.\n");
	}

	return EXIT_SUCCESS;
}

int alternativeTest(Square k, Square q) {
	return (k.x == q.x || k.y == q.y || abs(k.x - q.x) == abs(k.y - q.y));
}

// 2D ARRAY: (Needs to be flipped)
// (0,0) --------> (7,0)
//  |                |
//  |                |
//  |                |
// (0,7) --------> (7,7)

int queenAttacksKing(Square king_square, Square queen_square) {
	Square chessboard[BOARD_LEN][BOARD_LEN];
	createBoard(chessboard, king_square, queen_square);

	//Horizontal Scan:

	for (int i = 0; i < BOARD_LEN; i++) {
		if (chessboard[BOARD_LEN - queen_square.y][i].piece == KING) {
			return 1;
		}
	}

	//Vertical Scan.

	for (int j = 0; j < BOARD_LEN; j++) {
		if (chessboard[j][queen_square.x].piece == KING) {
			return 1;
		}
	}

	int x = queen_square.x;
	int y = BOARD_LEN - queen_square.y;

	while (x < BOARD_LEN && y < BOARD_LEN) {
		if (chessboard[y][x].piece == KING) {
			return 1;
		}
		x++;
		y++;
	}

	x = queen_square.x;
	y = BOARD_LEN - queen_square.y;
	while (x < BOARD_LEN && y >= 0) {
		if (chessboard[y][x].piece == KING) {
			return 1;
		}
		x++;
		y--;
	}

	x = queen_square.x;
	y = BOARD_LEN - queen_square.y;
	while (x >= 0 && y >= 0) {
		if (chessboard[y][x].piece == KING) {
			return 1;
		}
		x--;
		y--;

	}

	x = queen_square.x;
	y = BOARD_LEN - queen_square.y;
	while (x >= 0 && y < BOARD_LEN) {
		if (chessboard[y][x].piece == KING) {
			return 1;
		}
		x--;
		y++;

	}

	return 0;
}

void insertSquare(Square square, Square chessboard[BOARD_LEN][BOARD_LEN]) {
	chessboard[BOARD_LEN-square.y][square.x] = square;
}

void createBoard(Square chessboard[BOARD_LEN][BOARD_LEN], Square k, Square q) {
	Square input;
	int i = BOARD_LEN-1;
	while( i >= 0) {
		int j = 0;
		while (j < BOARD_LEN) {
			input.y = i;
			input.x = j;
			input.piece = EMPTY;
			chessboard[i][j] = input;
			j++;
		}
		i--;
	}


	insertSquare(k, chessboard);
	insertSquare(q, chessboard);

}

void printChessboard(Square chessboard[BOARD_LEN][BOARD_LEN], int x, int y) {
	int i = -1;
	while (i < BOARD_LEN) {
		if (i == -1) {
			printf("  ");
			int j = 0;
			while (j < BOARD_LEN) {
				printf("%c", 'A' + j);
				j++;
			}
			printf(" \n");
			printf("  ________ \n");
			i++;
			continue;
		}
		int j = -1;
		while (j < BOARD_LEN) {
			if (j == -1) {
				printf("%d|", BOARD_LEN -  i);
			} else {
				if (j == x && i == (BOARD_LEN - y)) {
					printf("x");
				} else {
					if (chessboard[i][j].piece == QUEEN) {
						printf("Q");
					} else if (chessboard[i][j].piece == KING) {
						printf("K");
					} else {
						printf(" ");
					}
				}
			}
			j++;
		}
		printf("|\n");
		i++;
	}
	printf("  -------- \n");
}
