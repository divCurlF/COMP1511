// Assignment 2 Final Card Down player.c
//
// Completed by
// Zac Sanchez (z5194994)
//
// Modified on 2018-10-26
// Emily Chen (Mon09-strings)

#include <stdio.h>
#include "player.h"

#define NUM_VALUES 16
#define NUM_SUITS 5
#define NUM_COLORS 5



// OUTINE MY STRATEGY
//
//	Heuristic: Attach a value to each card.
//	Formula: Value + 16*[# of value duplicates] + 16*[# of color duplicates] + 16*[# of suit duplicates]
//
//	Apply this formula to all indices in the hand.
//	Order of operations:
//	If there are active draw twos, always play a draw two.
//	Otherwise, play the card (not 0 a 2) that minimises heuristic score.
//	If none of these cards are left play a 2 prioritised heuristically
//	If no 2's are left play a one.
//
//	If playing any move is invalid try to draw a card, otherwise try to end the turn.
//
static int maxArrayIndex(int size, int array[size]);
static int calculateDuplicates(int dups);

static void updateHeuristicArray(int num_cards, Card cards[num_cards],
	int values[NUM_VALUES], int colors[NUM_COLORS],
	int suits[NUM_SUITS], int heuristic_card_values[num_cards]);

static int findBestCard(int size, int hvalues[size],
	int valid_indices[size]);

static playerMove chooseCard(Game game, int num_cards,
	int h_values[num_cards], int draw_two_indices[num_cards],
	int valid_indices[num_cards], int zero_indices[num_cards],
	int color_counters[NUM_COLORS], Card cards[num_cards],
	int valid_reg_move, int valid_two_move, int valid_zero_move);

static void initialiseZeroArray(int size, int array[size]);

static void initialiseArraysToZero(int num_cards,
	int h_values[num_cards], int valid_indices[num_cards],
	int draw_two_indices[num_cards], int zero_indices[num_cards]);

playerMove decideMove(Game game) {
	int num_cards = handCardCount(game);

	int value_counters[NUM_VALUES] = {0};
	int color_counters[NUM_COLORS] = {0};
	int suit_counters[NUM_SUITS] = {0};

	Card cards[num_cards];
	int h_values[num_cards];

	int valid_indices[num_cards];
	int draw_two_indices[num_cards];
	int zero_indices[num_cards];

	initialiseArraysToZero(num_cards, h_values, valid_indices,
		draw_two_indices, zero_indices);

	int valid_move_exists = FALSE;
	int valid_two_move = FALSE;
	int valid_zero_move = FALSE;
	int valid_regular_move = FALSE;


	playerMove move;
	move.action = PLAY_CARD;

	for (int i = 0; i < num_cards; i++) {
		Card c = handCard(game, i);
		value_counters[cardValue(c)]++;
		color_counters[cardColor(c)]++;
		suit_counters[cardSuit(c)]++;

		move.card = c;

		if (isValidMove(game, move)) {
			// We definitely A valid move, so we will play a card.
			valid_move_exists = TRUE;

			// should store these in an array and find the best one.
			if (cardValue(c) == 2) {
				valid_two_move = TRUE;
				draw_two_indices[i] = TRUE;
			// store all the zero card indicies.
			} else if (cardValue(c) == 0) {
				valid_zero_move = TRUE;
				zero_indices[i] = TRUE;
			} else {
				valid_regular_move = TRUE;
				valid_indices[i] = TRUE;
			}
		}
		cards[i] = c;
	}

	// If we have no valid move, we must draw or end turn.
	if (!valid_move_exists) {
		move.action = DRAW_CARD;
		if (!isValidMove(game, move)) {
		// If we aren't allowed to draw, we must only be able to end the turn.
			move.action = END_TURN;
		}
	} else {
		// At this point we must have a valid move, so we decide to play a card.

		updateHeuristicArray(num_cards, cards, value_counters,
			suit_counters, color_counters, h_values);

		move = chooseCard(game, num_cards, h_values, draw_two_indices,
			valid_indices, zero_indices, color_counters, cards,
			valid_regular_move, valid_two_move, valid_zero_move);

	}
	return move;
}

static playerMove chooseCard(Game game, int num_cards,
	int h_values[num_cards], int draw_two_indices[num_cards],
	int valid_indices[num_cards], int zero_indices[num_cards],
	int color_counters[NUM_COLORS], Card cards[num_cards],
	int valid_reg_move, int valid_two_move, int valid_zero_move)
{
	playerMove move;
	move.action = PLAY_CARD;
	int idx = 0;
	if (getActiveDrawTwos(game) > 0) {
		// Find the best draw two card to play if we need to play one.
		idx = findBestCard(num_cards, h_values, draw_two_indices);
		move.card = cards[idx];
	} else if (valid_reg_move) {
		// Prioritise removing non special cards from the hand.
		idx = findBestCard(num_cards, h_values, valid_indices);

		// If we want to play a change colour card, pick the colour we have the most of.
		if (cardValue(cards[idx]) == D) {
			int color_index = maxArrayIndex(NUM_COLORS, color_counters);
			move.nextColor = color_counters[color_index];
		}
		move.card = cards[idx];
	} else if (valid_two_move) {
		// If we only have two's or zero's left, choose two first.
		idx = findBestCard(num_cards, h_values, draw_two_indices);
		move.card = cards[idx];
	} else if (valid_zero_move) {
		// Now we should only have zeroes left, so play them.
		idx = findBestCard(num_cards, h_values, zero_indices);
		move.card = cards[idx];
	}
	return move;
}

// Return the index of the best playable card in the hand.
// Otherwise, if no valid moves are available, returns -1.
//
static int findBestCard(int size, int hvalues[size], int valid_indices[size]) {
	int best_idx = 0;

	for (int i = 0; i < size; i++) {
		// get the best current index in the hvalue array.
		best_idx = maxArrayIndex(size, hvalues);
		if (valid_indices[best_idx] == FALSE) {
			hvalues[best_idx] = 0;
		} else {
			return best_idx;
		}
	}

	return best_idx;
}

// Updates the heuristic value of each card in the hand.
void updateHeuristicArray(
	int num_cards,
	Card cards[num_cards],
	int values[NUM_VALUES],
	int colors[NUM_COLORS],
	int suits[NUM_SUITS],
	int heuristic_card_values[num_cards]
) {
	int card_value;

	// duplicate values of the card for each value, suit, color.
	int v_dups, c_dups, s_dups;

	// Total heuristic value;
	int heuristic_value;

	for (int i = 0; i < num_cards; i++) {
		Card c = cards[i];

		card_value = cardValue(c);

		if (card_value == 0) {
			card_value = 1;
		}

		// Default value
		heuristic_value = -1;

		v_dups = values[cardValue(c)];
		c_dups = colors[cardSuit(c)];
		s_dups = suits[cardColor(c)];

		v_dups = calculateDuplicates(v_dups);
		c_dups = calculateDuplicates(c_dups);
		s_dups = calculateDuplicates(s_dups);

		// Heuristic formula explained above.
		heuristic_value = card_value + 16 * (v_dups + c_dups + s_dups);
		heuristic_card_values[i] = heuristic_value;
	}
}

// Example output: if dups = 1 or 0 returns 0 (no duplicates).
// if dups = 5, returns 4 (4 duplicate cards).
static int calculateDuplicates(int dups) {
	int val = -1;
	if (dups > 1) {
		val = dups - 1;
	} else {
		val = 0;
	}
	return val;
}

static int maxArrayIndex(int size, int array[size]) {
	int max = 0;
	int index = 0;
	for (int i = 0; i < size; i++) {
		if (array[i] > max) {
			max = array[i];
			index = i;
		}
	}
	return index;
}

static void initialiseZeroArray(int size, int array[size]) {
	for (int i = 0; i < size; i++) {
		array[i] = 0;
	}
}

static void initialiseArraysToZero(int num_cards,
	int h_values[num_cards], int valid_indices[num_cards],
	int draw_two_indices[num_cards], int zero_indices[num_cards])
{
	initialiseZeroArray(num_cards, h_values);
	initialiseZeroArray(num_cards, valid_indices);
	initialiseZeroArray(num_cards, draw_two_indices);
	initialiseZeroArray(num_cards, zero_indices);
}
