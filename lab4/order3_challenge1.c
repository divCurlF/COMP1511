#include <stdio.h>

int main(void) {
	int a, b, c;
	printf("Enter integer: ");
	scanf("%d", &a);
	printf("Enter integer: ");
	scanf("%d", &b);
	printf("Enter integer: ");
	scanf("%d", &c);

	int first = (a<b)*(a<c)*a + (b<a)*(b<c)*b + (c<a)*(c<b)*c;
	int second = (a<b)*(a>c)*a + (a>b)*(a<c)*a + (b<a)*(b>c)*b + (b<c)*(b>a)*b + (c<a)*(c>b)*c + (c<b)*(c>a)*c;
	int third = (a>b)*(a>c)*a + (b>a)*(b>c)*b + (c>a)*(c>b)*c;

	printf("The integers in order are: %d %d %d\n", first, second, third);
	return 0;
}
