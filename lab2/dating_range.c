#include <stdio.h>

int main(void) {
	int age;
	printf("Enter your age: ");
	scanf("%d", &age);
	int lower = age/2 + 7;
	if (lower >= age) {
		printf("You are too young to be dating.\n");
	} else {
		int upper = 2*age - 14;
		printf("Your dating range is %d to %d years old.\n", lower, upper);
	}
}
