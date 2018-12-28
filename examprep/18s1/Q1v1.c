#include <stdio.h>

int main(void) {
	int upper, lower;
	printf("Enter lower: ");
	scanf("%d", &lower);
	printf("Enter upper: ");
	scanf("%d", &upper);
	
	int result = 1;
	
	int i = lower + 1;
	while (i < upper) {
		if (i % 2 != 0) {
			result = result * i;
		}
		i++;
	}
	printf("%d\n", result);
}
