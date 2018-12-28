//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

#define QUEUE_LEN 10
#define MAX_STRING_LEN 1024

void addFirst(char queue[QUEUE_LEN][MAX_STRING_LEN], char* input_string);
void printQueue(char queue[QUEUE_LEN][MAX_STRING_LEN], int size);

int main(int argc, char *argv[]) {
	//Throw an error if there isn't command argument

	if (argc != 2) {
			fprintf(stderr, "Need two cli args\n");
			exit(1);
	}

	// Open the file in read mode from argv[1]

	FILE *in = fopen(argv[1], "r");

	if (in == NULL) {
			fprintf(stderr, "FILE READ ERROR");
			exit(1);
	}

	// Instantiate a queue.
	char buffer[MAX_STRING_LEN];
	char queue[QUEUE_LEN][MAX_STRING_LEN];

	//Read in first ten values into the queue.
	int i = 0;
   	while (i < 10 && fgets(buffer, MAX_STRING_LEN, in) != NULL) {
		strcpy(queue[i],buffer);
		i++;
	}

	// Read in any subsequent values replacing the old ones.
	while (fgets(buffer, MAX_STRING_LEN, in) != NULL) {
		addFirst(queue, buffer);
	}

	// Print the contents of the queue (i will be len of file or 10).
	printQueue(queue, i);



	return EXIT_SUCCESS;
}

void addFirst(char queue[QUEUE_LEN][MAX_STRING_LEN], char* input_string) {

	//swaps all elements up the queue.
	int i = 0;
	while (i < QUEUE_LEN-1) {
			strcpy(queue[i],queue[i+1]);
			i++;
	}

	// Finally copies the new string into the arrray
	strcpy(queue[QUEUE_LEN-1], input_string);

	return;
}

void printQueue(char queue[QUEUE_LEN][MAX_STRING_LEN], int size) {
	int i = 0;
	while (i < size) {
			printf("%s", queue[i]);
			i++;
	}
}
