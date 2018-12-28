
#include <stdio.h>

int main(void) {
	int num;
	
	scanf("%d", &num);
	
	int evens[1000];
	int odds[1000];
	
	int even_iter = 0;
	int odd_iter = 0;
	
	while (num >= 0) {
		if (num % 2 == 0) {
			evens[even_iter] = num;
			even_iter++;
		} else {
			odds[odd_iter] = num;
			odd_iter++;
		}
		scanf("%d", &num);
	}
	
	
	printf("Odd numbers were: ");
	int i = 0;
	while (i < odd_iter) {
		printf("%d ", odds[i]);
		i++;
	}
	printf("\nEven numbers were: ");
	
	i = 0;
	while (i < even_iter) {
		printf("%d ", evens[i]);
		i++;
	}
	printf("\n");
}
