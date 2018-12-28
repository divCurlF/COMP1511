//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>

#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

typedef enum {
	RIGHT,
	UP,
	LEFT,
	DOWN
} Mode;

typedef struct _point {
	double x;
	double y;
} point;

int isInTriangle(point v1, point v2, point v3, point p);
double triangleSign(point v1, point v2, point v3);
void printBorder(int c);
double calcXOrd(int c, double xmin, double xmax, double x);
double calcYOrd(int r, double ymin, double ymax, double y);

int main(void) {

	double xmin, ymin, xmax, ymax, x1, x2, x3, y1, y2, y3;

	int r, c;
	printf("Enter the numbers: ");
	scanf("%d %d %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &r, &c, &xmin, &ymin, &xmax, &ymax, &x1, &y1, &x2, &y2, &x3, &y3);

	point p1 = {x1, y1};
	point p2 = {x2, y2};
	point p3 = {x3, y3};

	printBorder(c);
	double xcoord;
	double ycoord;
	point p;
	for (int y = r - 1; y >= 0; y--) {
		printf("|");
		for (int x = 0; x < c; x++) {
			xcoord = calcXOrd(c, xmin, xmax, (double) x);
			ycoord = calcYOrd(r, ymin, ymax, (double) y);
			p.x = xcoord;
			p.y = ycoord;
			if (isInTriangle(p1, p2, p3, p)) {
				printf("*");
			} else {
				printf(" ");
			}
		}
		printf("|\n");
	}
	printBorder(c);

}

double calcXOrd(int c, double xmin, double xmax, double x) {
	return xmin + (xmax - xmin) * x / (c - 1);
}

double calcYOrd(int r, double ymin, double ymax, double y) {
	return ymin + (ymax - ymin) * y / (r - 1);
}

void printBorder(int c) {
	printf("+");
	for (int i = 0; i < c; i++) {
		printf("-");
	}
	printf("+\n");
}


int isInTriangle(point v1, point v2, point v3, point p) {

	int t1, t2, t3;

	t1 = triangleSign(p, v1, v2) < 0.0;
	t2 = triangleSign(p, v2, v3) < 0.0;
	t3 = triangleSign(p, v3, v1) < 0.0;


	return (t1 == t2) && (t2 == t3);
}

double triangleSign(point v1, point v2, point v3) {
	return (v1.x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (v1.y - v3.y);
}

