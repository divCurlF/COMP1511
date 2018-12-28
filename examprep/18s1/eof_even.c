
#include <stdio.h>

int main(void) {
	int num;
	
	
	int evens[10000];
	int i = 0;
	while (scanf("%d", &num) == 1) {
		if (num % 2 == 0) {
			evens[i] = num;
			i++;
		}
	}
	
	int j = 0;
	while (j < i) {
		printf("%d ", evens[j]);
		j++;
	}

}
