// Assignment 2 Final Card Down testGame.c
//
// Completed by
// Zac Sanchez (z5194994)
//
// Modified on 2018-10-26
// Emily Chen (Mon09-strings)

#include <stdio.h>
#include <assert.h>

#include "Game.h"
#include "Card.h"

#define NUM_VALUES 16
#define NUM_SUITS 5
#define NUM_COLORS 5

// ==========================================================
// Helper methods for printing output to console.
// ==========================================================
static void compactPrintCard(Card c);
static void printPlayerHand(Game game, int player);
static void printGameState(Game game);

// ==========================================================
// CREDIT: methods inherited from stage2.c test file.
// ==========================================================
static Game initSimpleGame(void);
static int cardMatchesComponents(Card card, value v, color c, suit s);

// ==========================================================
// Helper methods for asserting which moves are valid.
// ==========================================================

static void validMove(Game game, int num_cards_in_hand,
	int valid_moves[num_cards_in_hand]);

static void validDraw(Game game, int valid);
static void validEnd(Game game, int valid);
static void checkNoValidCard(Game game);

// ==========================================================
// Helper methods for playing moves.
// ==========================================================
static void playEnd(Game game);
static void playDraw(Game game, value new_top_card_value,
	color new_top_card_color, suit new_top_card_suit,
	value new_hand_card_value, color new_hand_card_color,
	suit new_hand_card_suit);

static void playCard(Game game, int card_index, color color);

// ==========================================================
// Main helper method for checking the game state.
// Tests all functions specified in the API.
// ==========================================================
static void checkFullState(Game game, int curr_player, int top_disc_turn,
	int curr_turn, int num_turns, int prev_turn_player,
	int curr_turn_moves, int num_two_cards, int curr_color,
	int active_draw_twos, int hand_count, int curr_player_points
);
// ==========================================================
// Helper methods for each turn of the Simple Game
// ==========================================================
static Game initSimpleGame(void);
static void testEndOfGame(Game game);
static void testEmptyDeck(Game game);
static void skipToEmptyDeck(Game game);
static void testComplexDrawTwoPartTwo(Game game);
static void testComplexDrawTwoPartOne(Game game);
static void testIntermediateMoves(Game game);
static void testVoluntaryDrawMovesPart2(Game game);
static void testVoluntaryDrawMovesPart1(Game game);
static void testBasicDrawTwoMove(Game game);
static void testSkipMove(Game game);
static void testInitialPlayMoves(Game game);
static void testEndRound1(Game game);
static void testEndRound2(Game game);
static void testEndRound3(Game game);
static void testEndRound4(Game game);
static void testEndRound5(Game game);
static void testEndRound6(Game game);
static void testEndRound7(Game game);

// =========================================================
// Other game modes to further testing
// =========================================================
static Game initMinimalGame(void);
static void testEndGame1(void);
static void testEndGame2(void);
static void testInitGameEdge1(void);
static void testInitGameEdge2(void);

int main(void) {
	Game game = initSimpleGame();
	testInitialPlayMoves(game);
	printGameState(game);
	testSkipMove(game);
	printGameState(game);
	testBasicDrawTwoMove(game);
	printGameState(game);
	testVoluntaryDrawMovesPart1(game);
	printGameState(game);
	testVoluntaryDrawMovesPart2(game);
	printGameState(game);
	testIntermediateMoves(game);
	printGameState(game);
	testComplexDrawTwoPartOne(game);
	printGameState(game);
	testComplexDrawTwoPartTwo(game);
	printGameState(game);
	skipToEmptyDeck(game);
	printGameState(game);
	testEmptyDeck(game);
	printGameState(game);
	testEndOfGame(game);
	printGameState(game);
	destroyGame(game);

	testEndGame1();
	testEndGame2();
	testInitGameEdge1();
	testInitGameEdge2();
}

// ==========================================================
// METHODS FOR EACH TURN OF THE GAME.
// ==========================================================
static void testInitGameEdge2(void) {
	int deck_size = 32;
	value values[] = {
		ZERO, ONE, DRAW_TWO, THREE,
		FOUR, FIVE, ZERO, ONE,
		DRAW_TWO, THREE, FOUR, FIVE,
		ZERO, DRAW_TWO, THREE, FOUR,
		FIVE, ZERO, ONE, DRAW_TWO,
		THREE, FOUR, FIVE, ZERO,
		ONE, DRAW_TWO, FOUR, FIVE,
		A, THREE, FOUR, FIVE
	};

	color colors[] = {
		RED, RED, RED, RED,
		BLUE, BLUE, BLUE, BLUE,
		GREEN, GREEN, GREEN, GREEN,
		YELLOW, YELLOW, YELLOW, YELLOW,
		PURPLE, PURPLE, PURPLE, PURPLE,
		RED, RED, RED, RED,
		BLUE, BLUE, BLUE, BLUE,
		GREEN, GREEN, GREEN, GREEN
	};

	suit suits[] = {
		HEARTS, DIAMONDS, CLUBS, SPADES,
		QUESTIONS, HEARTS, DIAMONDS, CLUBS,
		SPADES, QUESTIONS, HEARTS, DIAMONDS,
		CLUBS, SPADES, QUESTIONS, HEARTS,
		DIAMONDS, CLUBS, SPADES, QUESTIONS,
		HEARTS, DIAMONDS, CLUBS, SPADES,
		QUESTIONS, HEARTS, DIAMONDS, CLUBS,
		SPADES, QUESTIONS, HEARTS, DIAMONDS
	};

	Game game = newGame(deck_size, values, colors, suits);
	checkFullState(game, 1, -1, 0, 1, -1, 0, 0, GREEN, 0, 7, 17);

	printf("Player 0 was skipped. Test Case passed!\n");
	destroyGame(game);
}

static void testInitGameEdge1(void) {
	int deck_size = 32;
	value values[] = {
		ZERO, ONE, DRAW_TWO, THREE,
		FOUR, FIVE, ZERO, ONE,
		DRAW_TWO, THREE, FOUR, FIVE,
		ZERO, DRAW_TWO, THREE, FOUR,
		FIVE, ZERO, ONE, DRAW_TWO,
		THREE, FOUR, FIVE, ZERO,
		ONE, DRAW_TWO, FOUR, FIVE,
		DRAW_TWO, THREE, FOUR, FIVE
	};

	color colors[] = {
		RED, RED, RED, RED,
		BLUE, BLUE, BLUE, BLUE,
		GREEN, GREEN, GREEN, GREEN,
		YELLOW, YELLOW, YELLOW, YELLOW,
		PURPLE, PURPLE, PURPLE, PURPLE,
		RED, RED, RED, RED,
		BLUE, BLUE, BLUE, BLUE,
		GREEN, GREEN, GREEN, GREEN
	};

	suit suits[] = {
		HEARTS, DIAMONDS, CLUBS, SPADES,
		QUESTIONS, HEARTS, DIAMONDS, CLUBS,
		SPADES, QUESTIONS, HEARTS, DIAMONDS,
		CLUBS, SPADES, QUESTIONS, HEARTS,
		DIAMONDS, CLUBS, SPADES, QUESTIONS,
		HEARTS, DIAMONDS, CLUBS, SPADES,
		QUESTIONS, HEARTS, DIAMONDS, CLUBS,
		SPADES, QUESTIONS, HEARTS, DIAMONDS
	};

	// This game is initalised with a draw_two on top.
	Game game = newGame(deck_size, values, colors, suits);
	checkFullState(game, 0, -1, 0, 1, -1, 0, 1, GREEN, 1, 7, 15);
	int valid_moves_p0[] = {0, 0, 0, 0, 1, 0, 0};
	validMove(game, handCardCount(game), valid_moves_p0);
	playCard(game, 4, -1);
	playEnd(game);
	int valid_moves_p1[] = {1, 0, 0, 1, 0, 0, 0};
	validMove(game, handCardCount(game), valid_moves_p1);
	playCard(game, 0, -1);
	playEnd(game);
	int valid_moves_p2[] = {0, 0, 0, 0, 0, 0, 1};
	validMove(game, handCardCount(game), valid_moves_p2);
	playCard(game, 6, -1);
	playEnd(game);
	int valid_moves_p3[] = {0, 0, 1, 0, 0, 0, 0};
	validMove(game, handCardCount(game), valid_moves_p3);
	playCard(game, 2, -1);
	playEnd(game);
	checkFullState(game, 0, 3, 4, 5, 3, 0, 5, PURPLE, 5, 6, 13);
	checkNoValidCard(game);

	int num_draws = 2*getActiveDrawTwos(game);
	int i = 0;

	playerMove move;
	move.action = DRAW_CARD;
	while (i < num_draws && gameWinner(game) == NOT_FINISHED) {
		playMove(game, move);
		i++;
	}

	assert(gameWinner(game) == NO_WINNER);

	printf("Game ends with no winner. Test case pased!\n");
	destroyGame(game);
}

static void testEndGame2(void) {
	// Identical to testEndGame1 except making sure the game does
	// not end prematurely if the player does not elect to pick up
	// when there are no cards left in the deck.

	Game endGame = initMinimalGame();

	playerMove move;
	move.action = DRAW_CARD;
	playMove(endGame, move);
	playEnd(endGame);


	// Second player plays a valid move. Game should not end.

	playCard(endGame, 4, -1);
	assert(gameWinner(endGame) == NOT_FINISHED);
	playEnd(endGame);

	// Two cards in discard pile, no card in deck. Player
	// should be able to draw a card as discard pile is flipped.
	// Player first tries to draw a card.
	playMove(endGame, move);

	cardMatchesComponents(topDiscard(endGame), THREE, GREEN, SPADES);

	// There will be no cards in the deck as the discard pile got flipped,
	// the top card of the deck was given to the first player.
	assert(getDeckCard(endGame, 0) == NULL);

	assert(gameWinner(endGame) == NOT_FINISHED);
	playEnd(endGame);

	// Now there are no cards in the deck, one card in the discard pile
	// an attempt to draw a card results in the game ending.
	printf("Attempting to draw a card\n");
	playMove(endGame, move);

	assert(gameWinner(endGame) == NO_WINNER);

	printf("Game ended with no winner. Test case passed!\n\n");
	destroyGame(endGame);
}

static void testEndGame1(void) {
	printf("\n");
	Game endGame = initMinimalGame();
	cardMatchesComponents(topDiscard(endGame), THREE, GREEN, SPADES);

	playerMove move;
	move.action = DRAW_CARD;
	playMove(endGame, move);
	cardMatchesComponents(getHandCard(endGame, 0, 0), FOUR, GREEN,
		QUESTIONS);
	assert(getDeckCard(endGame, 0) == NULL);

	validDraw(endGame, 0);
	playEnd(endGame);

	// Now if the player attempts to draw a move, the game should finish
	// with no winnder.
	playMove(endGame, move);
	assert(gameWinner(endGame) == NO_WINNER);

	printf("Game ended with no winner!\nTest Case passed.\n\n");

	destroyGame(endGame);
}

static Game initMinimalGame(void) {
	int deck_size = 30;

	value values[] = {
		ZERO, ONE, DRAW_TWO, THREE,
		FOUR, FIVE, ZERO, ONE,
		DRAW_TWO, THREE, FOUR, FIVE,
		ZERO, DRAW_TWO, THREE, FOUR,
		FIVE, ZERO, ONE, DRAW_TWO,
		THREE, FOUR, FIVE, ZERO,
		ONE, DRAW_TWO, FOUR, FIVE,
		THREE, FOUR
	};

	color colors[] = {
		RED, RED, RED, RED,
		BLUE, BLUE, BLUE, BLUE,
		GREEN, GREEN, GREEN, GREEN,
		YELLOW, YELLOW, YELLOW, YELLOW,
		PURPLE, PURPLE, PURPLE, PURPLE,
		RED, RED, RED, RED,
		BLUE, BLUE, BLUE, BLUE,
		GREEN, GREEN
	};

	suit suits[] = {
		HEARTS, DIAMONDS, CLUBS, SPADES,
		QUESTIONS, HEARTS, DIAMONDS, CLUBS,
		SPADES, QUESTIONS, HEARTS, DIAMONDS,
		CLUBS, SPADES, QUESTIONS, HEARTS,
		DIAMONDS, CLUBS, SPADES, QUESTIONS,
		HEARTS, DIAMONDS, CLUBS, SPADES,
		QUESTIONS, HEARTS, DIAMONDS, CLUBS,
		SPADES, QUESTIONS
	};

	Game minimalgame = newGame(deck_size, values, colors, suits);
	return minimalgame;
}

static void testEndRound1(Game game) {
	playCard(game, 2, -1);
	playEnd(game);
	playCard(game, 4, -1);
	playEnd(game);
	playCard(game, 10, -1);
	playEnd(game);

	printGameState(game);
	checkFullState(game, 0, 30, 31, 32, 3, 0, 0, RED, 0, 12, 93);
	printf("\n");
}
static void testEndRound2(Game game) {
	playCard(game, 9, -1);
	playEnd(game);
	playCard(game, 3, -1);
	playEnd(game);
	playCard(game, 5, -1);
	playEnd(game);
	playCard(game, 8, -1);
	playEnd(game);

	printGameState(game);
	checkFullState(game, 1, 34, 35, 36, 0, 0, 0, GREEN, 0, 6, 58);
	printf("\n");
}
static void testEndRound3(Game game) {
	playCard(game, 5, -1);
	playEnd(game);
	playCard(game, 5, -1);
	playEnd(game);
	playCard(game, 10, -1);
	playEnd(game);
	playCard(game, 9, -1);
	playEnd(game);
	printGameState(game);
	checkFullState(game, 1, 38, 39, 40, 0, 0, 0, RED, 0, 5, 53);
}

static void testEndRound4(Game game) {
	playCard(game, 4, -1);
	playEnd(game);
	playCard(game, 4, -1);
	playEnd(game);
	playCard(game, 9, -1);
	playEnd(game);
	playCard(game, 7, -1);
	playEnd(game);
	printGameState(game);
	checkFullState(game, 1, 42, 43, 44, 0, 0, 0, YELLOW, 0, 4, 44);
}

static void testEndRound5(Game game) {
	playCard(game, 2, -1);
	playEnd(game);
	playCard(game, 0, -1);
	playEnd(game);
	playCard(game, 0, -1);
	playEnd(game);
	playCard(game, 7, -1);
	playEnd(game);
	printGameState(game);
	checkFullState(game, 1, 46, 47, 48, 0, 0, 0, RED, 0, 3, 39);
}

static void testEndRound6(Game game) {
	playDraw(game, NINE, GREEN, HEARTS, EIGHT, GREEN, QUESTIONS);
	playEnd(game);
	playCard(game, 0, -1);
	playEnd(game);
	playCard(game, 1, -1);
	playEnd(game);
	playCard(game, 2, -1);
	playEnd(game);
	checkFullState(game, 2, 50, 51, 52, 0, 0, 0, PURPLE, 0, 2, 9);
}

static void testEndRound7(Game game) {
	playCard(game, 0, -1);
	playEnd(game);
	playCard(game, 0, YELLOW);
	playEnd(game);
	playCard(game, 5, -1);
	playEnd(game);
	playDraw(game, A, GREEN, DIAMONDS, NINE, GREEN, HEARTS);
	playEnd(game);
	checkFullState(game, 2, 53, 55, 56, 1, 0, 0, YELLOW, 0, 1, 1);
}

static void testEndOfGame(Game game) {

	printf("Playing Random moves until the end of the game..\n");

	testEndRound1(game);
	testEndRound2(game);
	testEndRound3(game);
	testEndRound4(game);
	testEndRound5(game);
	testEndRound6(game);
	testEndRound7(game);

	playCard(game, 0, -1);
	assert(gameWinner(game) == 2);
	printf("Player 2 Wins!\n");

	printf("Test Case Passed!\n");
}


static void testEmptyDeck(Game game) {

	printf("One card left in the deck.\n");
	playerMove drawMove;
	drawMove.action = DRAW_CARD;
	playMove(game, drawMove);
	validEnd(game, 1);
	playEnd(game);

	printf("Testing the flip mechanics after a draw\n.");
	// There are no cards in the deck at this stage.
	playMove(game, drawMove);
	value vals[] = {8, 9, A, 0, 1, 2, 8, 2, 2};
	color cols[] = {
		GREEN, GREEN, GREEN, BLUE,
		RED, RED, RED, BLUE, YELLOW};
	suit suits[] = {
		QUESTIONS, HEARTS, DIAMONDS,
		DIAMONDS, DIAMONDS, CLUBS, SPADES,
		SPADES, QUESTIONS};
	Card card;
	for (int i = 0; i < 9; i++) {
		card = getDeckCard(game, i);
		cardMatchesComponents(card, vals[i], cols[i], suits[i]);
	}
	playEnd(game);
	printf("Success!\n\n");
}

static void skipToEmptyDeck(Game game) {

	checkFullState(game, 1, 14, 16, 17, 0, 0, 2, YELLOW, 0, 7, 36);

	int valid_moves[] = {1, 1, 0, 0, 0, 1, 0};
	validMove(game, handCardCount(game), valid_moves);
	validDraw(game, 1);
	validEnd(game, 0);

	// Playing a Yellow 3 of Hearts
	playCard(game, 0, -1);
	checkFullState(game, 1, 16, 16, 17, 0, 1, 0, YELLOW, 0, 6, 33);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);

	printf("Skipping forward 10 moves (Forcing everyone to draw cards) \n\n");
	playerMove drawMove, endMove;
	drawMove.action = DRAW_CARD;
	endMove.action = END_TURN;
	for (int i = 0; i < 9; i++) {
		playMove(game, drawMove);
		playMove(game, endMove);
	}
	checkFullState(game, 3, 16, 26, 27, 2, 0, 0, YELLOW, 0, 11, 106);
}

static void testComplexDrawTwoPartTwo(Game game) {
	checkFullState(game, 0, 14, 15, 16, 3, 0, 2, YELLOW, 2, 5, 35);

	// Player has no 2's, so they must draw 4 cards.
	checkNoValidCard(game);
	validDraw(game, 1);
	validEnd(game, 0);

	//Making sure that an attempt to play a card doesn't change the game state.
	playCard(game, 0, -1);
	checkFullState(game, 0, 14, 15, 16, 3, 0, 2, YELLOW, 2, 5, 35);

	//Draw all 4 cards
	playDraw(game, 5, YELLOW, CLUBS, 4, YELLOW, DIAMONDS);
	checkFullState(game, 0, 14, 15, 16, 3, 1, 2, YELLOW, 2, 6, 39);
	checkNoValidCard(game);
	validDraw(game, 1);
	validEnd(game, 0);

	playDraw(game, 6, YELLOW, SPADES, 5, YELLOW, CLUBS);
	checkFullState(game, 0, 14, 15, 16, 3, 2, 2, YELLOW, 2, 7, 44);
	checkNoValidCard(game);
	validDraw(game, 1);
	validEnd(game, 0);

	playDraw(game, 7, YELLOW, QUESTIONS, 6, YELLOW, SPADES);
	checkFullState(game, 0, 14, 15, 16, 3, 3, 2, YELLOW, 2, 8, 50);
	checkNoValidCard(game);
	validDraw(game, 1);
	validEnd(game, 0);

	playDraw(game, 8, PURPLE, HEARTS, 7, YELLOW, QUESTIONS);
	checkFullState(game, 0, 14, 15, 16, 3, 4, 2, YELLOW, 2, 9, 57);

	// Drawn all 4 cards, only valid action is to end the turn.
	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);
}

static void testComplexDrawTwoPartOne(Game game) {
	checkFullState(game, 2, 11, 13, 14, 1, 0, 0, RED, 0, 6, 39);

	int valid_moves_p2[] = {1, 0, 1, 0, 0, 1};
	validMove(game, handCardCount(game), valid_moves_p2);
	validDraw(game, 1);
	validEnd(game, 0);

	// Playing a Blue 2 of Spades
	playCard(game, 2, -1);
	checkFullState(game, 2, 13, 13, 14, 1, 1, 1, BLUE, 1, 5, 37);
	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);

	checkFullState(game, 3, 13, 14, 15, 2, 0, 1, BLUE, 1, 10, 86);

	int valid_moves_p3[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	validMove(game, handCardCount(game), valid_moves_p3);
	validDraw(game, 1);
	validEnd(game, 0);

	// Playing a Yellow 2 of Questions
	playCard(game, 0, -1);
	checkFullState(game, 3, 14, 14, 15, 2, 1, 2, YELLOW, 2, 9, 84);

	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);
}

static void testIntermediateMoves(Game game) {
	checkFullState(game, 0, 5, 11, 12, 3, 0, 1, RED, 0, 6, 43);

	int valid_moves_p0[] = {0, 0, 1, 1, 1, 1};
	validMove(game, handCardCount(game), valid_moves_p0);
	validDraw(game, 1);
	validEnd(game, 0);

	// Playing Red 8 of Spades.
	playCard(game, 3, -1);
	checkFullState(game, 0, 11, 11, 12, 3, 1, 0, RED, 0, 5, 35);

	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);

	checkFullState(game, 1, 11, 12, 13, 0, 0, 0, RED, 0, 6, 33);

	int valid_moves_p1[] = {1, 0, 0, 1, 1, 1};
	validMove(game, handCardCount(game), valid_moves_p1);
	validDraw(game, 1);
	validEnd(game, 0);

	playDraw(game, 4, YELLOW, DIAMONDS, 3, YELLOW, HEARTS);
	checkFullState(game, 1, 11, 12, 13, 0, 1, 0, RED, 0, 7, 36);

	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);
}


static void testVoluntaryDrawMovesPart1(Game game) {
	checkFullState(game, 0, 5, 7, 8, 3, 0, 1, RED, 0, 5, 28);

	int valid_moves_p0[] = {0, 1, 1, 1, 1};
	validMove(game, handCardCount(game), valid_moves_p0);
	validDraw(game, 1);
	validEnd(game, 0);

	// Draw a card voluntarily
	playDraw(game, 0, YELLOW, CLUBS, F, YELLOW, DIAMONDS);
	checkFullState(game, 0, 5, 7, 8, 3, 1, 1, RED, 0, 6, 43);

	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);

	checkFullState(game, 1, 5, 8, 9, 0, 0, 1, RED, 0, 5, 33);

	int valid_moves_p1[] = {0, 1, 0, 1, 1};
	validMove(game, handCardCount(game), valid_moves_p1);
	validDraw(game, 1);
	validEnd(game, 0);

	playDraw(game, 1, YELLOW, SPADES, 0, YELLOW, CLUBS);
	checkFullState(game, 1, 5, 8, 9, 0, 1, 1, RED, 0, 6, 33);

	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);

	checkFullState(game, 2, 5, 9, 10, 1, 0, 1, RED, 0, 5, 38);

}

static void testVoluntaryDrawMovesPart2(Game game) {
	int valid_moves_p2[] = {1, 1, 0, 0, 1};
	validMove(game, handCardCount(game), valid_moves_p2);
	validDraw(game, 1);
	validEnd(game, 0);

	playDraw(game, 2, YELLOW, QUESTIONS, 1, YELLOW, SPADES);
	checkFullState(game, 2, 5, 9, 10, 1, 1, 1, RED, 0, 6, 39);

	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);

	checkFullState(game, 3, 5, 10, 11, 2, 0, 1, RED, 0, 9, 84);

	int valid_moves_p3[] = {0, 0, 1, 0, 0, 0, 0, 1, 1};
	validMove(game, handCardCount(game), valid_moves_p3);
	validDraw(game, 1);
	validEnd(game, 0);

	playDraw(game, 3, YELLOW, HEARTS, 2, YELLOW, QUESTIONS);
	checkFullState(game, 3, 5, 10, 11, 2, 1, 1, RED, 0, 10, 86);

	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);
}

static void testBasicDrawTwoMove(Game game) {

	checkFullState(game, 2, 4, 5, 6, 1, 0, 0, RED, 0, 6, 40);

	int valid_moves_p2[] = {0, 0, 0, 0, 1, 1};
	validMove(game, handCardCount(game), valid_moves_p2);
	validDraw(game, 1);
	validEnd(game, 0);

	// Playing a Red 2 of Clubs
	playCard(game, 5, -1);
	// There is now an active draw two on the top of the discard pile.
	checkFullState(game, 2, 5, 5, 6, 1, 1, 1, RED, 1, 5, 38);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);
	checkFullState(game, 3, 5, 6, 7, 2, 0, 1, RED, 1, 7, 57);

	// Player has no cards with value 2, so he must draw.
	checkNoValidCard(game);
	validDraw(game, 1);
	validEnd(game, 0);

	// Check that trying to play a card does not change game state.
	playCard(game, 0, -1);
	checkFullState(game, 3, 5, 6, 7, 2, 0, 1, RED, 1, 7, 57);

	// Play the draw and ensure the top of the deck has the correct card
	// and ensure that the player has actually received the previous top of deck.
	playDraw(game, E, YELLOW, HEARTS, D, GREEN, QUESTIONS);
	checkFullState(game, 3, 5, 6, 7, 2, 1, 1, RED, 1, 8, 70);

	// Still only valid to draw a card.
	checkNoValidCard(game);
	validDraw(game, 1);
	validEnd(game, 0);

	// Trying to play a card doesn't change the state.
	playCard(game, 0, -1);
	checkFullState(game, 3, 5, 6, 7, 2, 1, 1, RED, 1, 8, 70);

	playDraw(game, F, YELLOW, DIAMONDS, E, YELLOW, HEARTS);

	// active draw two still active until we end the turn.
	checkFullState(game, 3, 5, 6, 7, 2, 2, 1, RED, 1, 9, 84);

	// Make sure it is no longer valid to draw a card or play a card. Only
	// Allowed to end the turn.
	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);
}

static void testSkipMove(Game game) {

	// Player 3 got skipped!
	checkFullState(game, 0, 2, 3, 4, 2, 0, 0, GREEN, 0, 6, 28);

	int valid_moves_p0[] = {1, 1, 0, 0, 0, 1};
	validMove(game, handCardCount(game), valid_moves_p0);
	validDraw(game, 1);
	validEnd(game, 0);

	// Playing a Blue 0 of Diamonds.
	playCard(game, 1, -1);
	checkFullState(game, 0, 3, 3, 4, 2, 1, 0, BLUE, 0, 5, 28);
	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);

	checkFullState(game, 1, 3, 4, 5, 0, 0, 0, BLUE, 0, 6, 34);

	int valid_moves_p1[] = {1, 1, 1, 0, 0, 1};
	validMove(game, handCardCount(game), valid_moves_p1);
	validDraw(game, 1);
	validEnd(game, 0);

	// Playing a Red 1 of Diamonds
	playCard(game, 5, -1);
	checkFullState(game, 1, 4, 4, 5, 0, 1, 0, RED, 0, 5, 33);
	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);
}



static void testInitialPlayMoves(Game game) {
	checkFullState(game, 0, -1, 0, 1, -1, 0, 0, GREEN, 0, 7, 36);

	int valid_moves_p0[] = {1, 1, 1, 1, 1, 0, 1};
	validMove(game, handCardCount(game), valid_moves_p0);
	validDraw(game, 1);
	validEnd(game, 0);

	// Playing an 8 Green of Questions
	playCard(game, 0, -1);
	checkFullState(game, 0, 0, 0, 1, -1, 1, 0, GREEN, 0, 6, 28);
	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);

	checkFullState(game, 1, 0, 1, 2, 0, 0, 0, GREEN, 0, 7, 43);

	int valid_moves_p1[] = {1, 1, 0, 0, 1, 0, 0};
	validMove(game, handCardCount(game), valid_moves_p1);
	validDraw(game, 1);
	validEnd(game, 0);
	// Playing a 9 Green of Hearts
	playCard(game, 0, -1);
	checkFullState(game, 1, 1, 1, 2, 0, 1, 0, GREEN, 0, 6, 34);
	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);

	checkFullState(game, 2, 1, 2, 3, 1, 0, 0, GREEN, 0, 7, 50);

	int valid_moves_p2[] = {1, 1, 0, 0, 1, 0, 0};
	validMove(game, handCardCount(game), valid_moves_p2);
	validDraw(game, 1);
	validEnd(game, 0);

	//Playing a Green A of Diamonds.
	playCard(game, 0, -1);
	checkFullState(game, 2, 2, 2, 3, 1, 1, 0, GREEN, 0, 6, 40);
	checkNoValidCard(game);
	validDraw(game, 0);
	validEnd(game, 1);
	playEnd(game);
}

// ==========================================================
// STATIC HELPER METHODS HERE
// ==========================================================

// Asserts which PLAY_CARD moves are valid in the current players hand.
static void validMove(Game game, int num_cards_in_hand,
	int valid_moves[num_cards_in_hand])
{
	printf("Checking PLAYER %d's valid moves...\n", currentPlayer(game));
	Card card;
	for (int i = 0; i < num_cards_in_hand; i++) {
		card = getHandCard(game, currentPlayer(game), i);
		compactPrintCard(card);
		playerMove move = {PLAY_CARD, -1, card};
		printf(":%d ", isValidMove(game, move));
		assert(isValidMove(game, move) == valid_moves[i]);
	}
	printf("\n");
}

// Asserts that it is valid to draw a card.
static void validDraw(Game game, int valid) {
	if (valid == 0) {
		printf("Ensuring it is not valid to draw a card\n");
	} else {
		printf("Ensuring it is valid to draw a card\n");
	}
	playerMove move = {DRAW_CARD, -1, NULL};
	assert(isValidMove(game, move) == valid);
}

// Asserts the player is allowed to end their turn.
static void validEnd(Game game, int valid) {
	if (valid == 0) {
		printf("Ensuring it is not valid to end the turn\n");
	} else {
		printf("Ensuring it is valid to end the turn\n");
	}
	playerMove moveEnd = {END_TURN, -1, NULL};
	assert(isValidMove(game, moveEnd) == valid);
}
// Asserts the player has no PLAY_CARD moves.
static void checkNoValidCard(Game game) {
	printf("Making sure the player cannot play a card\n");
	int num_cards = handCardCount(game);
	int post_valid_arr[num_cards];
	for (int i = 0; i < num_cards; i++) {
		post_valid_arr[i] = 0;
	}
	validMove(game, num_cards, post_valid_arr);
}

// Plays the card at index card_index, and specifies a color if the card
// has value D. I have employed the convention of giving the color field
// the value -1 if the card did not have value D.
static void playCard(Game game, int card_index, color color) {
	playerMove move;

	int curr_player = currentPlayer(game);
	printf("Making PLAYER %d's move of ", curr_player);
	Card card = getHandCard(game, curr_player, card_index);
	compactPrintCard(card);
	printf("\n");

	if (color > 0) {
		move.nextColor = color;
	}

	move.card = card;
	move.action = PLAY_CARD;
	if (isValidMove(game, move)) {
		playMove(game, move);
		assert(topDiscard(game) == card);
	} else {
		printf("Invalid move!\n");
	}
}

// Plays the move END_TURN.
static void playEnd(Game game) {
	playerMove move_end;
	printf("Attempting to end player %d's turn\n", currentPlayer(game));
	move_end.action = END_TURN;
	if (!isValidMove(game, move_end)) {
		printf("Invalid Move!\n");
	}
	playMove(game, move_end);
}

// Plays a draw move and checks the new top of the deck is correct and that
// the player who drew the card has the new card in their hand.
static void playDraw(Game game, value new_top_card_value,
	color new_top_card_color, suit new_top_card_suit,
	value new_hand_card_value, color new_hand_card_color,
	suit new_hand_card_suit)
{
	playerMove draw;
	int curr_player = currentPlayer(game);

	printf("Making PLAYER %d draw a card\n", curr_player);
	draw.action = DRAW_CARD;
	playMove(game, draw);

	printf("Checking the deck was correctly updated\n");
	assert(cardMatchesComponents(getDeckCard(game, 0),
		new_top_card_value, new_top_card_color, new_top_card_suit));

	printf("Checking the player received a ");
	compactPrintCard(getHandCard(game, curr_player, 0));
	printf("\n");
	assert(cardMatchesComponents(getHandCard(game, curr_player, 0),
		new_hand_card_value, new_hand_card_color, new_hand_card_suit));
}

// Tests all functions defined in the API.
static void checkFullState(Game game, int curr_player, int top_disc_turn,
	int curr_turn, int num_turns, int prev_turn_player,
	int curr_turn_moves, int num_two_cards, int curr_color,
	int active_draw_twos, int hand_count, int curr_player_points)
{
	printf("Checking the game state\n");
	assert(currentPlayer(game) == curr_player);
	assert(getTopDiscardTurnNumber(game) == top_disc_turn);
	assert(currentTurn(game) == curr_turn);
	assert(numTurns(game) == num_turns);
	assert(getPreviousTurnPlayer(game) == prev_turn_player);
	assert(currentTurnMoves(game) == curr_turn_moves);
	assert(getNumberOfTwoCardsAtTop(game) == num_two_cards);
	assert(getCurrentColor(game) == curr_color);
	assert(getActiveDrawTwos(game) == active_draw_twos);
	assert(handCardCount(game) == hand_count);
	assert(playerPoints(game, currentPlayer(game)) == curr_player_points);
}

// Initialises the game.
static Game initSimpleGame(void) {
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
		GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
		GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW,
		YELLOW, YELLOW, YELLOW, PURPLE, PURPLE, PURPLE, PURPLE, PURPLE,
		PURPLE, PURPLE, PURPLE, PURPLE, PURPLE
	};

	suit suits[] = {
		HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS,
		CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES,
		QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS,
		DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS,
		SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS,
		HEARTS, DIAMONDS, CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS,
		CLUBS, SPADES, QUESTIONS, HEARTS, DIAMONDS, CLUBS, SPADES,
		QUESTIONS
	};

	Game game = newGame(deck_size, values, colors, suits);
	printf("\n");
	return game;
}




// Check that all the VCS components specified,  match that of the card.
static int cardMatchesComponents(Card card, value v, color c, suit s) {
	return cardValue(card) == v && cardColor(card) == c && cardSuit(card) == s;
}

// Prints out a card in the format VCS [value, color, suit].
// Abbreviated so only the first letter of each field printed.
static void compactPrintCard(Card c) {
	if (c == NULL) {
		printf("NULL");
	} else {

		char *valueStrings[NUM_VALUES] = {
			"0", "1", "2", "3",
			"4", "5", "6", "7",
			"8", "9", "A", "B",
			"C", "D", "E", "F"
		};

		char *colorStrings[NUM_COLORS] = {
			"R", "B", "G", "Y", "P"
		};

		char *suitStrings[NUM_SUITS] = {
			"H", "D", "C", "S", "Q"
		};

		printf("%s%s%s", valueStrings[cardValue(c)],
			colorStrings[cardColor(c)], suitStrings[cardSuit(c)]);
	}
}

static void printGameState(Game game) {
	for (int i = 0; i < NUM_PLAYERS; i++) {
		printf("Player %d's hand: ", i);
		printPlayerHand(game, i);
		printf("\n");
	}

	printf("Cards in the deck currently: ");

	printf("[ ");

	int i = 0;
	while (getDeckCard(game, i) != NULL) {
		compactPrintCard(getDeckCard(game, i));
		printf(" ");
		i++;
	}
	printf("]\n");

	printf("Cards in the discard pile currently: ");

	printf("[ ");
	i = 0;
	while (getDiscardPileCard(game, i) != NULL) {
		compactPrintCard(getDiscardPileCard(game, i));
		printf(" ");
		i++;
	}

	printf("]\n");

	printf("Top Card: ");
	compactPrintCard(topDiscard(game));
	printf("\n");
	printf("Current player is Player %d\n\n", currentPlayer(game));
}

// Prints out in python format the players hand.
static void printPlayerHand(Game game, int player) {
	printf("[ ");
	for (int i = 0; i < playerCardCount(game, player); i++) {
		compactPrintCard(getHandCard(game, player, i));
		printf(" ");
	}
	printf("]");
}
