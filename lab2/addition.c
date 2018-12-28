#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

int main(void) {
	int a, b;
	printf("Please enter two integers: ");
	scanf("%d", &a);
	scanf("%d", &b);

	printf("%d + %d = %d\n", a, b, a+b);

	return EXIT_SUCCESS;
}
