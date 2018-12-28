#include <stdio.h>

int main(void) {
	int number;
	scanf("%d", &number);
	if (number > 0) {
		printf("You have entered a positive number.\n");
	} else if (number < 0) {
		printf("You have entered a negative number.\n");
	} else {
		printf("You have enetered zero.\n");
	}
}
