


#include <stdio.h>
#include <stdlib.h>

#include "mandelbrot.h"



int main (void) {
	struct complex c = {0.05, 0.5};

	struct complex d = {1,1};
	
	struct complex e = {-1,0};
	struct complex f = {1.7, -0.3};

	printf("%d %d %d %d", escapeSteps(c),escapeSteps(d),escapeSteps(e),escapeSteps(f));

	//double y = -1.0;
	//double y = -1.0;
	//while (y < 1.0) {
        	//double x = -1.0;
		//while (x < 1.0){
			//c.re = x;
			//c.im = y;
			//int n = escapeSteps(c);
			//printf("%d",n);
			//if (n == 256){
				//printf("*");
				//pixel[y][x].red = 255;
				//pixel[y][x].blue = 255;
				//pixel[y][x].green = 255;

			//} else {
				//printf(" ");
				//pixel[y][x].red = 0;
				//pixel[y][x].blue = 0;
				//pixel[y][x].green = 0;

			//}
		 //x = x + 0.05;
		
		//}
		//y= y + 0.05;
		//printf("\n");

	//}
   //int n = escapeSteps(
   //printf("%d", n);}
}

