// Assignment 2 Final Card Down Game.c
//
// Completed by
// Zac Sanchez (z5194994)
//
// Modified on 2018-10-26
// Emily Chen (Mon09-strings)

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "Card.h"
#include "Game.h"

#define DEFAULT_HAND 7
#define NUM_VALUES 16
#define NUM_SUITS 5
#define NUM_COLORS 5

typedef struct _listCard *ListCard;
typedef struct _player *Player;
typedef struct _deck *Deck;
typedef struct _gamestate *GameState;

struct _listCard {
	Card card;
	ListCard next;
};

// A deck is an ADT for a linked list of Cards,
// The deck will be used as an abstraction of a list of cards.

struct _deck {
	// Keep track of the deck.
	int num_cards;

	// Keeps track of the value of the points in the deck.
	// Will be useful to avoid recalculating player points.
	int value;
	// Stack of cards in the deck.
	// Keep track of the top of the deck
	ListCard top;
};

// Store the game data structures.
typedef struct _game {
	Deck draw_pile;
	Deck discard_pile;

	//The players are an array of decks representing their hands.
	//The index of the array is the player's id.
	Deck players[NUM_PLAYERS];

	// Keeps track of arrays with number of each value, color or suit.
	int *v_count;
	int *c_count;
	int *s_count;

	int curr_player;
	int curr_player_draws;
	int curr_player_moves;
	int curr_player_played_card;
	int prev_player;

	Card curr_card;
	color curr_colour;

	int active_draws;
	int num_two_cards;
	int skipped;

	int turn_number;
	int last_played_turn;

	int num_cards;
	int game_winner;

} game;
static void initialiseStateVariables(Game newgame);
static ListCard newListCard(Card card);
static void addToTop(Deck deck, Card card);
static Deck newDeck(void);
static Card popCard(Deck deck);
static void flipDeck(Game game);
// static void reverseDeck(Deck deck);
static void freeDeck(Deck deck);
static void distributeCards(Deck first_deck, Game game);
static Card retrieveCard(Deck hand, playerMove move);

static void initialise_arrays(int *v_count, int *c_count, int *s_count);

static void addCardsToDeck(int deck_size, Game newgame,
	value values[deck_size], color colors[deck_size],
	suit suits[deck_size], int *v_count, int *s_count,
	int *c_count);

static int containsCard(Deck hand, Card card);
static int isValidCard(Game game, Card played_card);
static Card getNthCard(Deck deck, int n);

static int validPlayMove(Game game, playerMove move);
static int validDrawMove(Game game);
static int validEndMove(Game game);

static void playCardMove(Game game, playerMove move);
static void playDrawMove(Game game);
static void playEndMove(Game game);


Game newGame(int deckSize, value values[], color colors[], suit suits[]) {
	// malloc a new game.
	Game newgame = malloc(sizeof(game));

	// Initialise game state variables and the game decks.
	newgame->num_cards = deckSize;
	newgame->draw_pile = newDeck();
	newgame->discard_pile = newDeck();

	//To be used for retrieval functions,
	//counts the numbers of each type of card in the deck.
	int *v_count = malloc(NUM_VALUES * sizeof(value));
	int *s_count = malloc(NUM_SUITS * sizeof(suit));
	int *c_count = malloc(NUM_COLORS * sizeof(color));

	initialise_arrays(v_count, s_count, c_count);
	addCardsToDeck(deckSize, newgame, values, colors, suits,
		v_count, c_count, v_count);

	// Add all the cards in the given arrays to the deck of draw cards.
	newgame->v_count = v_count;
	newgame->s_count = s_count;
	newgame->c_count = c_count;

	//Allocate memory for the player hands.
	int i = 0;
	while (i < NUM_PLAYERS) {
		newgame->players[i] = newDeck();
		i++;
	}

	//Deals the cards to the players.
	distributeCards(newgame->draw_pile, newgame);

	// Push the first card in the draw_pile
	// onto the stack of the discard_pile.
	addToTop(newgame->discard_pile, popCard(newgame->draw_pile));

	// initialises all the state variables for the game.
	initialiseStateVariables(newgame);
	return newgame;
}


void destroyGame(Game game) {
	int i = 0;
	while (i < NUM_PLAYERS) {
		freeDeck(game->players[i]);
		i++;
	}
	freeDeck(game->draw_pile);
	freeDeck(game->discard_pile);

	free(game->c_count);
	free(game->s_count);
	free(game->v_count);
	free(game);
}

int numCards(Game game) {
	return game->num_cards;
}

int numOfSuit(Game game, suit suit) {
	return game->s_count[suit];
}

int numOfColor(Game game, color color) {
	return game->c_count[color];
}

int numOfValue(Game game, value value) {
	return game->v_count[value];
}

int currentPlayer(Game game) {
	return game->curr_player;
}

int currentTurn(Game game) {
	return game->turn_number;
}

Card topDiscard(Game game) {
	return game->curr_card;
}

int numTurns(Game game) {
	return currentTurn(game) + 1;
}

int currentTurnMoves(Game game) {
	return game->curr_player_moves;
}

int getNumberOfTwoCardsAtTop(Game game) {
	return game->num_two_cards;
}

int getCurrentColor(Game game) {
	return game->curr_colour;
}

int getPreviousTurnPlayer(Game game) {
	return game->prev_player;
}

int getTopDiscardTurnNumber(Game game) {
	return game->last_played_turn;
}

int getActiveDrawTwos(Game game) {
	// This number will always be even.
	return game->active_draws / 2;
}

int handCardCount(Game game) {
	return game->players[game->curr_player]->num_cards;
}

Card handCard(Game game, int card) {

	// No negative index.
	if (card < 0) {
		return NULL;
	}

	// Ensure the desired index exists in the player's hand.
	if (game->players[game->curr_player]->num_cards < card + 1) {
		return NULL;
	} else {
		ListCard curr = game->players[game->curr_player]->top;

		int i = 0;
		while (curr != NULL && i < card) {
			i++;
			curr = curr->next;
		}
		return curr->card;
	}
}

int isValidMove(Game game, playerMove move) {

	if (move.action == PLAY_CARD) {
		return validPlayMove(game, move);

	} else if (move.action == DRAW_CARD) {

		return validDrawMove(game);
	} else if (move.action == END_TURN) {

		return validEndMove(game);
	}

	//Should never get here, but if the action
	//itself was invalid, the move is invalid.
	return FALSE;
}

// ---------------------------------------------------------
//The following functions must NOT be called by a player
// You can use the following functions to test your Game ADT
// ---------------------------------------------------------

void playMove(Game game, playerMove move) {
	if (isValidMove(game, move)) {
		game->curr_player_moves++;

		if (move.action == DRAW_CARD) {
			playDrawMove(game);
		} else if (move.action == PLAY_CARD) {
			playCardMove(game, move);
		} else {
			playEndMove(game);
		}
	}
}

int gameWinner(Game game) {
	return game->game_winner;
}

Card getDeckCard(Game game, int n) {
	return getNthCard(game->draw_pile, n);
}

Card getDiscardPileCard(Game game, int n) {
	return getNthCard(game->discard_pile, n);
}

Card getHandCard(Game game, int player, int n) {
	return getNthCard(game->players[player],n);
}

int playerCardCount(Game game, int player) {
	return game->players[player]->num_cards;
}

int playerPoints(Game game, int player) {
	return game->players[player]->value;
}

// ========================================================================
// MY STATIC FUNCTIONS ARE WRITTEN FROM HERE ON
// ========================================================================
//
static void addCardsToDeck(int deck_size, Game newgame,
	value values[deck_size], color colors[deck_size],
	suit suits[deck_size], int *v_count,
	int *c_count, int *s_count)
{
	int i = deck_size-1;
	while (i >= 0) {
		// Create a card from the array of values, colours and suits.
		Card card = newCard(values[i], colors[i], suits[i]);

		// Increment each of the counters for number of cards.
		v_count[values[i]]++;
		s_count[suits[i]]++;
		c_count[colors[i]]++;

		// Add the card to the deck.
		addToTop(newgame->draw_pile, card);
		i--;
	}
}

static void initialiseStateVariables(Game newgame) {

	// Initalise all other state variables for the game.
	newgame->curr_card = newgame->discard_pile->top->card;
	newgame->curr_colour = cardColor(newgame->curr_card);
	newgame->curr_player = 0;
	newgame->curr_player_draws = 0;
	newgame->curr_player_moves = 0;
	newgame->prev_player = -1;
	newgame->last_played_turn = -1;
	newgame->turn_number = 0;
	newgame->game_winner = NOT_FINISHED;
	newgame->num_two_cards = 0;
	newgame->active_draws = 0;
	newgame->skipped = FALSE;
	newgame->curr_player_played_card = FALSE;

	// Edge cases when the first card is a special card
	if (cardValue(newgame->curr_card) == A) {
		newgame->curr_player++;
	} else if (cardValue(newgame->curr_card) == DRAW_TWO) {
		newgame->num_two_cards++;
		newgame->active_draws += 2;
	}
}


// Helper function to retrieve the nth card from a deck.
static Card getNthCard(Deck deck, int n) {
	ListCard curr = deck->top;
	int i = 0;
	while (curr != NULL) {
		if (i == n) {
			return curr->card;
		}
		curr = curr->next;
		i++;
	}
	return NULL;
}

// Checks if the given deck contains the specific card.
static int containsCard(Deck hand, Card card) {
	ListCard curr = hand->top;
	while (curr != NULL) {
		if (curr->card == card) {
			return TRUE;
		}
		curr = curr->next;
	}
	return FALSE;
}

// Helper function for isValidPlayMove, checks if the card has same
// colour, suit or value as top discard OR is a zero, OR matches
// the current colour of the game.
static int isValidCard(Game game, Card played_card) {
	if (cardValue(played_card) == ZERO) {
		return TRUE;
	} else {
		return (cardSuit(topDiscard(game)) == cardSuit(played_card) ||
			game->curr_colour == cardColor(played_card) ||
			cardValue(topDiscard(game)) == cardValue(played_card)
		);
	}
}


// FINDS and REMOVES a card from a deck. Function is only ever called by
// playMove, hand won't be empty unless a bug exists in game runner.
static Card retrieveCard(Deck deck, playerMove move) {
	ListCard curr = deck->top;

	//	Sanity Check, if this ever happens the game should have ended.
	if (curr == NULL) {
		return NULL;
	}

	// If its the first card in the deck that needs to be removed.
	if (curr->card == move.card) {
		Card card = curr->card;
		deck->top = curr->next;
		deck->value = deck->value - cardValue(card);
		free(curr);
		deck->num_cards--;
		return card;
	}

	// Otherwise perform regular linked list deletion.
	while (curr->next != NULL) {

		// We have found the card.
		if (curr->next->card == move.card) {

			// Storing the return card.
			ListCard temp = curr->next;
			Card card = curr->next->card;
			curr->next = temp->next;
			deck->value = deck->value - cardValue(card);
			free(temp);

			deck->num_cards--;
			return card;
		}
		curr = curr->next;
	}
	return NULL;
}

// Helper function for updating the game state when a player
// wants to draw a card.
static void playDrawMove(Game game) {

	// Game ends if trying to draw a card when deck is empty and
	// when there is only one card left in the discard pile.
	if (game->draw_pile->num_cards == 0 &&
		game->discard_pile->num_cards == 1
	) {
		game->game_winner = NO_WINNER;

	} else {

		game->curr_player_draws++;

		if (game->draw_pile->num_cards == 0) {
			// Any cards below the top most draw two card are put in the deck.
			// The number of active draw twos does not change though.
			if (cardValue(game->curr_card) == DRAW_TWO) {
				game->num_two_cards = 1;
			}

			// Performs the flip mechanics
			flipDeck(game);
		}

		//Move Card from draw pile to hand.
		addToTop(game->players[game->curr_player],
			popCard(game->draw_pile));

	}
}

// Helper function for updating the game state when a player
// wants to play a card.
static void playCardMove(Game game, playerMove move) {
		Card cardToPlay = retrieveCard(
			game->players[game->curr_player], move);

		addToTop(game->discard_pile, cardToPlay);

		// Updating state variables
		game->curr_card = cardToPlay;
		game->last_played_turn = game->turn_number;
		game->curr_colour = cardColor(cardToPlay);
		game->curr_player_played_card = TRUE;


		if (game->players[game->curr_player]->num_cards == 0) {
			game->game_winner = game->curr_player;
		}

		// Case of changing colour.
		if (cardValue(move.card) == D) {
			game->curr_colour = move.nextColor;

		}

		if (cardValue(move.card) == A) {
			game->skipped = TRUE;
		}

		if (cardValue(move.card) == DRAW_TWO) {
			game->num_two_cards++;
			game->active_draws += 2;
		} else {
			game->num_two_cards = 0;
		}
}

// Helper function for updating the game state when a player
// wants to end a turn.
static void playEndMove(Game game) {
	// Move action must have been an END_TURN.
	game->turn_number++;
	game->prev_player = game->curr_player;

	// Reset the number of active draws.
	if (game->active_draws == game->curr_player_draws) {
		game->active_draws = 0;
	}

	// Increment by two if a skip was played.
	if (!game->skipped) {
		game->curr_player = (game->curr_player + 1) % 4;
	} else {
		game->curr_player = (game->curr_player + 2) % 4;
		game->skipped = FALSE;
	}

	// Current player has all state variables reset
	game->curr_player_moves = 0;
	game->curr_player_draws = 0;
	game->curr_player_played_card = FALSE;
}


// Helper function for testing whether it is valid to play a card.
static int validPlayMove(Game game, playerMove move) {

	// If the player has already moved
	if (game->curr_player_moves != 0) {
		return FALSE;
	}

	// If the player doesn't have the card:
	if (!containsCard(game->players[game->curr_player], move.card)) {
		return FALSE;
	} else {

		// If the card at the top is an active draw card make sure they play a draw two.
		if (game->active_draws != 0) {
			return (cardValue(move.card) == DRAW_TWO);

		// Otherwise make sure card has same value suit or colour.
		} else {
			return isValidCard(game, move.card);
		}
	}
}

// Helper function for testing whether it is valid to draw a card.
static int validDrawMove(Game game) {

	// If the player has already played a card, cannot draw a card.
	if (game->curr_player_played_card) {
		return FALSE;
	}

	if (game->active_draws > 0) {

		// Once the player has drawn all active draws, he cannot draw any further.
		if (game->curr_player_draws == game->active_draws) {
			return FALSE;
		}
		// Must draw a card if there are still active_draws left.
		return TRUE;

	// Make sure we haven't drawn a card before voluntarily drawing.
	} else {
		return (game->curr_player_draws == 0);
	}
}

// Helper function for testing whether it is valid to end a move.
static int validEndMove(Game game) {
	// If the player hasn't moved
	if (game->curr_player_played_card == 0) {

		// If The player hasn't drawn a card.
		if (game->curr_player_draws == 0) {
			return FALSE;
		}

		// Hasn't drawn all the cards yet
		if (game->active_draws > game->curr_player_draws) {
			return FALSE;
		}

		// Otherwise the player hasn't moved but has drawn at least one card.
	}
	// The player has moved or drawn.
	return TRUE;
}

// Distributes the cards to all the players.
static void distributeCards(Deck draw_pile, Game game) {
	int i = 0;
	while (i < NUM_PLAYERS*DEFAULT_HAND) {
		addToTop(game->players[i % 4], popCard(draw_pile));
		i++;
	}
}

// Creates a ListCard structure that holds card information
static ListCard newListCard(Card card) {
	ListCard newCard = malloc(sizeof(struct _listCard));
	if (newCard == NULL) {
		fprintf(stderr, "Out of memory.\n");
		return NULL;
	}
	newCard->next = NULL;
	newCard->card = card;
	return newCard;
}

// Creates the Deck datatype to be used for player hands,
// the draw pile and the discard pile.
static Deck newDeck(void) {
	Deck deck = malloc(sizeof(struct _deck));

	if (deck == NULL) {
		fprintf(stderr, "Out of memory");
		return NULL;
	}
	deck->value = 0;
	deck->num_cards = 0;
	deck->top = NULL;
	return deck;
}

// Adds a single card to the top of a deck. Equivalent to a
// push operation for a stack.
static void addToTop(Deck deck, Card card) {
	ListCard newCard = newListCard(card);
	if (deck->top == NULL) {
		deck->top = newCard;
	} else {
		newCard->next = deck->top;
		deck->top = newCard;
	}
	deck->value += cardValue(card);
	deck->num_cards++;
}

// Removes the top card from a deck. Equivalent to the pop
// operation for a stack.
static Card popCard(Deck deck) {
	// sanity check
	if (deck == NULL) {
		return NULL;

	// Can't pop from an empty stack.
	} else if (deck->top == NULL) {
		return NULL;

	// Only one card in the deck.
	} else if (deck->top->next == NULL) {
		Card temp = deck->top->card;
		free(deck->top);
		deck->top = NULL;
		deck->num_cards--;
		deck->value = 0;
		return temp;

	// Otherwise: at least two cards in the deck:
	} else {
		Card topCard = deck->top->card;
		ListCard temp = deck->top->next;
		deck->value = deck->value - cardValue(topCard);
		deck->num_cards--;
		free(deck->top);
		deck->top = temp;
		return topCard;
	}
}

// Code to flip the deck once the draw pile becomes empty.
static void flipDeck(Game game) {
	// Temporarily store the top card of the draw pile.
	Card temp_card = popCard(game->discard_pile);

	int num_cards = game->discard_pile->num_cards;
	int i = 0;
	while (i < num_cards) {
		// Removing from the top and adding to a stack inserts
		// in reverse order.
		addToTop(game->draw_pile, popCard(game->discard_pile));
		i++;
	}
	addToTop(game->discard_pile, temp_card);
}


// Free all memory associated with a deck structure.
static void freeDeck(Deck deck) {
	ListCard curr = deck->top;
	if (curr == NULL) {
		free(deck);
		return;
	}
	while (curr != NULL) {
		ListCard temp = curr;
		destroyCard(temp->card);
		curr = curr->next;
		free(temp);
	}
	free(deck);
}

// Initialises the arrays that will store the number of suits, colors and values
// in the original deck. Only called in newGame.
static void initialise_arrays(int *v_count, int *c_count, int *s_count)
{
	for (int i = 0; i < NUM_VALUES; i++) {
			v_count[i] = 0;
	}
	for (int i = 0; i < NUM_COLORS; i++) {
			c_count[i] = 0;
	}
	for (int i = 0; i < NUM_SUITS; i++) {
			s_count[i] = 0;
	}
}

