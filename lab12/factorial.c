//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)

long long factorial (long long n);

long long factorial(long long n) {
	if (n == 0) {
		return 1;
	} else {
		return n*factorial(n -1);
	}
}
