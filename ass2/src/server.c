//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#include "Game.h"
#include "player.h"
#include "Card.h"

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

#define NUM_VALUES 16
#define NUM_SUITS 5
#define NUM_COLORS 5

Game init_game(void);
playerMove getUserMove(Game game);
void compactPrintCard(Card c);
void printPlayerHand(Game game, int player);
void printDeck(Game game);
void printGameInfo(Game game);
char * suitString(int suit);
char * valueString(int value);
char * colorString(int color);

int main(void) {

	Game game = init_game();
	playerMove move;
	int curr_player;

	printf("======FINAL CARD DOWN SERVER=====\n");
	printf("======MEDIUM MODE SELECTED=====\n");
	printf("Have fun!\n\n");

	while (gameWinner(game) == NOT_FINISHED) {
		printGameInfo(game);
		curr_player = currentPlayer(game);
		move = decideMove(game);
		if (move.action == PLAY_CARD) {
			printf("Player %d plays a ", curr_player);
			compactPrintCard(move.card);
			printf("\n");
		} else if (move.action == DRAW_CARD) {
			printf("Player %d draws a card.\n", curr_player);
		} else {
			printf("Player %d ends their turn.\n", curr_player);
		}

		playMove(game, move);

		int winner = gameWinner(game);
		if (winner != NOT_FINISHED) {
			if (winner == 4) {
				printf("No winner. Boring.");
			} else {
				printf("Player %d won! Congratulations.\n", winner);
			}
		}
	}
	destroyGame(game);

	return EXIT_SUCCESS;
}

void printGameInfo(Game game) {

	printf("Turn: %d Top Card: ", currentTurn(game)
	);

	compactPrintCard(topDiscard(game));
	printf(" Color: %s", colorString(getCurrentColor(game)));
	printf("\n");

	printf("Deck: ");
	printDeck(game);
	printf("\n");

	for (int i = 0; i < NUM_PLAYERS; i++) {
		printf("Player %d's hand: ", i);
		printPlayerHand(game, i);
		printf("\n");
	}
	printf("\n");
}

void printDeck(Game game) {
	Card c = getDeckCard(game, 0);
	printf("[ ");
	int i = 0;
	while (c != NULL) {
		compactPrintCard(c);
		printf(" ");
		c = getDeckCard(game, i);
		i++;
	}
	printf("]");
}

void printPlayerHand(Game game, int player) {
	int num_cards = playerCardCount(game, player);
	printf("[ ");
	Card c;
	for (int i = 0; i < num_cards; i++) {
		c = getHandCard(game, player, i);
		compactPrintCard(c);
		printf(" ");
	}
	printf("]");
}

void compactPrintCard(Card c) {
    if (c == NULL) {
        printf("NULL");
    } else {
        printf("%s%s%s",
			valueString(cardValue(c)),
			colorString(cardColor(c)),
			suitString(cardSuit(c))
      	);
    }
}

char * colorString(int color) {
	char *colorStrings[NUM_COLORS] = {"R", "B", "G", "Y", "P"};
	return colorStrings[color];
}

char * valueString(int value) {
	char *valueStrings[NUM_VALUES] = {
		"0", "1", "2", "3",
        "4", "5", "6", "7",
    	"8", "9", "A", "B",
        "C", "D", "E", "F"
	};
	return valueStrings[value];
}

char * suitString(int suit) {
	char *suitStrings[NUM_SUITS] = {"H", "D", "C", "S", "Q"};
	return suitStrings[suit];
}

playerMove getUserMove(Game game) {
	playerMove move;

	int index;
	printf("Player %d's turn.\n", currentPlayer(game));
	printf("Enter the index to play card, -1 to draw, -2 to end turn.\n");
	if (scanf("%d", &index) == EOF) {
		printf("Emergency Shutdown initiated.\n");
		exit(1);
	}

	if (index < -2) {
		move.action = -1;
		return move;
	}

	if (index == -1) {
		move.action = DRAW_CARD;
	} else if (index == -2) {
		move.action = END_TURN;
	} else {
		Card selected_card = handCard(game, index);
		if (selected_card == NULL) {
			move.action = -1;
			return move;
		}
		if (cardValue(selected_card) == D) {
			printf("Choose your colour: ");
			int selected_color;
		   	scanf("%d", &selected_color);
			getchar();
			move.nextColor = selected_color;
		}
		move.card = selected_card;
		move.action = PLAY_CARD;
	}
	return move;
}

Game init_game(void) {
    int deck_size = 50;
    value values[] = {
        ZERO, ONE, DRAW_TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
        A, B, C, D, E, F, ZERO, ONE, DRAW_TWO, THREE,
        FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, A, B, C, D,
        E, F, ZERO, ONE, DRAW_TWO, THREE, FOUR, FIVE, SIX, SEVEN,
        EIGHT, NINE, A, B, C, D, E, F, ZERO, ONE
    };

    color colors[] = {
        RED, RED, RED, RED, RED, RED, RED, RED, RED, RED,
        BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
        GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
        YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
        PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE
    };

    suit suits[] = {
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,
        HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS
    };

    Game game = newGame(deck_size, values, colors, suits);
    printf("\n");
    return game;
}

