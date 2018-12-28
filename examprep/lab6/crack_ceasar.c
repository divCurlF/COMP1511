
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ALPH 26
#define MAX_TEXT 10000

void read_frequency_file(FILE *f, int frequencies[ALPH]);
int read_input(char input[MAX_TEXT], int input_freq[ALPH]);
int findShift(int input_freq[ALPH], int eng_freq[ALPH]);
void printDeciphered(int num_chars, char input[], int shift);

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Program usage: ./crack_ceasar <filename>");
	}
	

	FILE *f = fopen(argv[1], "r");
	int eng_freq[ALPH] = {0};
	
	read_frequency_file(f, eng_freq);
	fclose(f);
	
	int input_freq[ALPH] = {0};
	char input[MAX_TEXT];
	
	int num_chars = read_input(input, input_freq);
	int shift = findShift(input_freq, eng_freq);
	
	printDeciphered(num_chars, input, shift);
	
	
	return 0;
}

void printDeciphered(int num_chars, char input[], int shift) {
	int i = 0;
	while ( i < num_chars) {
		if (isalpha(input[i])) {
			if (isupper(input[i])) {
				putchar((input[i] - 'A' + shift) % 26 + 'A');
			} else if (islower(input[i])) {
				putchar((input[i] - 'a' + shift) % 26 + 'a');
			}
		} else {
			putchar(input[i]);
		}
		i++;
	}
}

void read_frequency_file(FILE *f, int frequencies[ALPH]) {
	int c = fgetc(f);
	while (c != EOF) {
		if (isalpha(c)) {
			frequencies[tolower(c) - 'a']++;
		}
		c = fgetc(f);
	}
}

int read_input(char input[MAX_TEXT], int input_freq[ALPH]) {
	
	char c = getchar();
	
	int size = 0;
	while (c != EOF) {
		
		if (isalpha(c)) {
			input_freq[tolower(c) - 'a']++;
		}

		input[size] = c;
		size++;
		c = getchar();
	}
	
	return size;
}

int findShift(int input_freq[ALPH], int eng_freq[ALPH]) {

	int min_shift = 0;
	double min_error;
	
	
	// LOOP over all possible shifts.
	int shift = 0;
	while (shift < ALPH) {
	
		// Loop through all entries for each shift.
		int i = 0;
		double error = 0;
		while (i < ALPH) {
			error += pow((input_freq[(i + shift) % ALPH] - eng_freq[i]), 2);
			i++;
		}
		
		if (shift == 0) {
			min_error = error;
		}

		
		if (error < min_error) {
			min_shift = shift;
			min_error = error;
		}
		shift++;
	}
	
	// Extremely important: we are figuring out optimal shift from enciphered->deciphered,
	// But instead we really want to return teh inverse of that decipher -> encipher.
	// Shifting english forward by minshift <==> shifting deciphered back by ALPH - minshift.
	return ALPH - min_shift;
}


