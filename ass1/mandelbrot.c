// Assignment 1 Mandelbrot
//
// Completed by
// Zac Sanchez (z5194994)
//
// Modified on 2018-08-14
// Emily Chen (Mon10-lab)

#include <stdio.h>
#include <math.h>
// Add your own #includes here

#include "mandelbrot.h"
#include "pixelColor.h"

// Add your own #defines here
#define MAX_STEPS 256

// Add your own function prototypes here
static struct complex arrayMap(
		int x, int y, double zoom,
		struct complex center
);

static double complexAbsSquared(struct complex c);
static struct complex mandelIter(struct complex zn, struct complex c);
static struct complex complexSq(struct complex c);
static struct complex complexAdd(struct complex z1, struct complex z2);

// Take a pixel grid and and the path from the web browser used to
// request the 'tile'.
//
// The requestPath will be in the form "/mandelbrot/2/{zoom}/{x}/{y}.bmp".
// In the query, 'x' and 'y' are decimals and describe the 'center' of the
// tile and need to be converted into a complex number.
// 'zoom' is an integer representing the zoom level for the tile.
void serveMandelbrot(
	struct pixel pixels[TILE_SIZE][TILE_SIZE],
	char *requestPath
) {
	struct complex center = {0.0, 0.0};
	int z = 7;

	sscanf(
		requestPath,
		"/mandelbrot/2/%d/%lf/%lf.bmp",
		&z, &center.re, &center.im
	);

	// Use drawMandelbrot to draw the immage.
	drawMandelbrot(pixels, center, z);
}

// Draw a single Mandelbrot tile, by calculating and colouring each of
// the pixels in the tile.
//
// Your function "returns" this tile by filling in the `pixels` 2D array
// that is passed in to your function.
//
// The `pixels` array is TILE_SIZE high and TILE_SIZE wide.
// The bottom left corner of the image is pixels[0][0].
//
// `center` is a complex number, representing the center of the tile.
// `z` is used to calculate the distance between each pixel in the image.
// Each pixel is 2^(-z) apart from each other.

void drawMandelbrot(
	struct pixel pixels[TILE_SIZE][TILE_SIZE],
    struct complex center,
	int z
) {
	// Calculate this here to avoid doing it multiple times.
	double zoom = pow(2,-z);

	// Nested to loop to enter values into 2D array.
	int x = 0;
	while (x < TILE_SIZE) {
		int y = 0;
		while (y < TILE_SIZE) {
			struct complex complex_num = arrayMap(x,y,zoom,center);
			int steps = escapeSteps(complex_num);
			pixels[y][x] = pixelColor(steps);
			y++;
		}
		x++;
	}
}

/* arrayMap: Maps each (x,y) pair in array to the associated complex number with zoom factor.
 * params: x, y [array coords with (0,0) at bot-left, z (zoom), center (complex num to be in center of image)].
 *
 * LOGIC: begin at negative half the tile size, and add on the ordinate (x/y).
 * The ordinates run from 0 to TILE_SIZE so we get all the pixels this way, with center at (0,0).
 * Multiply by 2^{-z} as we map the original spacing of 1 between adjacent ordinates to 2^{-z}.
 * Finally add on the center to "shift" (0,0) to (Re(center), Im(center)).
 */
static struct complex arrayMap(
		int x, int y, double zoom,
		struct complex center
) {
	struct complex result;
	result.re = (- TILE_SIZE / 2 + x)*zoom + center.re;
	result.im = (- TILE_SIZE / 2 + y)*zoom + center.im;
	return result;
}

// Determine the number of steps required to escape the Mandelbrot set,
// for the given complex number `c`.
int escapeSteps(struct complex c) {

	// Count number of interations.
   	int steps = 0;

	// Initialise starting number z_n at (0,0).
	struct complex zn = {0.0, 0.0};

	// Loop until |zn|^2 < 4 (equiv to |zn| < 2)
	while (complexAbsSquared(zn) < 4) {

		// Break loop and return when we go over step limit.
		if (steps == MAX_STEPS) {
			return NO_ESCAPE;
		}

		zn = mandelIter(zn, c);
		steps++;
	}

	// Steps will be number of iterations.
    	return steps;
}

// Returns squared modulus of a complex number
static double complexAbsSquared(struct complex c) {
	return c.re*c.re + c.im*c.im;
}

//Returns the next number in mandelbrot iteration
static struct complex mandelIter(struct complex zn, struct complex c) {
	return complexAdd(complexSq(zn), c);
}

//Returns square of a complex number
static struct complex complexSq(struct complex c) {
	struct complex z;
	z.re = c.re*c.re - c.im*c.im;
	z.im = 2*c.re*c.im;
	return z;
}

//Adds two complex numbers
static struct complex complexAdd(struct complex z1, struct complex z2) {
	struct complex z3;
	z3.re = z1.re + z2.re;
	z3.im = z1.im + z2.im;
	return z3;
}

