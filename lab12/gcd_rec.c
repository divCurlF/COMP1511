//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)

int gcdRec(int a, int b);

int gcdRec(int a, int b) {
	if (b == 0) {
		return a;
	}
	return gcdRec(b, a%b);
}

