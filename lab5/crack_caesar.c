//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)


#define ALPH_SIZE 26
void printFreqArr(double n, int count[ALPH_SIZE]);
int arr_min(double arr[ALPH_SIZE]);
int crack_caesar(int encrypt[ALPH_SIZE], int decrypt[ALPH_SIZE], double num_encrypted, double num_decrypted);
char caesar_shift(char c, int shift);
void printArr(double arr[]);

int main(int argc, char *argv[]) {


	FILE *stream = fopen(argv[1], "r");
	if (stream == NULL) {
			perror(argv[1]);
			return 1;
	}

	//Initialise decrypt freq. array.
	int decrypted_counts[ALPH_SIZE] = {0};
	double num_decrypted = 0.0;

	// Loop through the file and store data into freq array.
	int c = fgetc(stream);
	while (c != EOF) {
		if (isalpha(c)) {
			decrypted_counts[tolower(c) - 'a']++;
			num_decrypted++;
		}
		c = fgetc(stream);
	}
	//Initalise an array to store stdin.
	char encrypted_text[10000];

	// Initalise array that encrypted letter frequencies.
	int encrypted_counts[ALPH_SIZE] = {0};
	double num_encrypted = 0.0;

	// Add all stdin to freq array and storage array.
	int size = 0;
	c = getchar();
	while (c != EOF) {
		encrypted_text[size] = c;
		size++;
		if (isalpha(c)) {
			encrypted_counts[tolower(c) - 'a']++;
			num_encrypted++;
		}
		c = getchar();
	}

	// Find the optimal shift that will decipher the text.
	int optimal_shift = crack_caesar(encrypted_counts,
									decrypted_counts,
									num_encrypted,
									num_decrypted);

	// Output decrypted text.
	int i = 0;
	while (i < size) {
		putchar(caesar_shift(encrypted_text[i], optimal_shift));
		i++;
	}

	return EXIT_SUCCESS;
}

// Print function for debugging.
void printFreqArr(double n, int count[ALPH_SIZE]) {
	int i = 0;
	while (i < ALPH_SIZE) {
		double frequency = count[i] / n;
		printf("'%c' %lf %d \n", i + 'a', frequency, count[i]);
		i++;
	}
}

int crack_caesar(int encrypt[ALPH_SIZE], int decrypt[ALPH_SIZE], double num_encrypted, double num_decrypted) {
		double shift_losses[ALPH_SIZE] = {0.0};

		/* Loop through all shifts, then calculate for each shift the mean square error
		of the difference between the decryption frequency and the
		encryption frequency of each letter in the alphabet.
		*/

		int shift = 0;
		while (shift < ALPH_SIZE) {
				int i = 0;
				double loss = 0.0;
				while (i < ALPH_SIZE) {
						double decrypt_freq = decrypt[i] / num_decrypted;
						double encrypt_freq = encrypt[(i+shift) % ALPH_SIZE] / num_encrypted;
						loss += pow(decrypt_freq - encrypt_freq, 2);
						i++;
				}
				shift_losses[shift] = loss;
				shift++;
		}
		int min_loss_index = arr_min(shift_losses);

		// We find optimal index to go from encrypt to decrypt, however we need to invert this!
		int min_shift_index = abs(min_loss_index - ALPH_SIZE);

		return min_shift_index;
}

// Finds the minimum of an array.
int arr_min(double arr[ALPH_SIZE]) {
		double min = arr[0];
		int min_shift = 0;
		int i = 0;
		while (i < ALPH_SIZE) {
			if (arr[i] < min) {
					min = arr[i];
					min_shift = i;
			}
			i++;
		}
		return min_shift;
}

// Computes the caesar shift of a character.
char caesar_shift(char c, int shift) {
	int new_index = 0;
	if (islower(c)) {
		int index = c - 'a';
		new_index = (index + shift) % 26;
		return new_index + 'a';
	} else if (isupper(c)) {
		int index = c - 'A';
		new_index = (index + shift) % 26;
		return new_index + 'A';
	}
	return c;
}

// Array print function for debugging.
void printArr(double arr[ALPH_SIZE]) {
		int i = 0;
		printf("\n[");
		while ( i < ALPH_SIZE) {
				printf("%lf ", arr[i]);
				i++;
		}
		printf("]\n");
}
