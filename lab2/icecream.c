#include <stdio.h>
#include <stdlib.h>

#define MONEY 10
#define EXIT_SUCCESS 0

int main(void) {
	int scoops, cost;

	printf("How many scoops? ");
	scanf("%d", &scoops);
	printf("How many dollars does each scoop cost? ");
	scanf("%d", &cost);

	if (cost*scoops <= MONEY) {
		printf("You have enough money!\n");
	} else {
		printf("Oh no, you don't have enough money :(\n");
	}

	return EXIT_SUCCESS;
}

