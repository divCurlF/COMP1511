
#include <stdio.h>

int main(void) {
	int num;
	
	int nums[10000];
	
	int i = 0;
	
	while (scanf("%d", &num) == 1) {
		nums[i] = num;
		i++;
	}
	
	int value = nums[i-1];
	
	int result = 0;
	
	int j = 0;
	while (j < i) {
		if (nums[j] == value) {
			result++;
		}
		j++;
	}
	
	printf("%d\n", result);
	return 0;

}
