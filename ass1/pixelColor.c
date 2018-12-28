// Assignment 1 Mandelbrot: Pixel Color
//
// Completed by
// Zac Sanchez (z5194994)
//
// Modified on 2018-08-14
// Tutor's name (Mon10-lab)

#include "mandelbrot.h"
#include "pixelColor.h"

static struct pixel shadesOfBlueRedYellow(int steps);
static struct pixel getPixel(int red, int green, int blue);

// This function should take a number (of steps taken to escape the
// Mandelbrot set), and convert it to a color.
//
// You have artistic licence here, so make your Mandelbrot look amazing.
//

struct pixel pixelColor(int steps) {
    return shadesOfBlueRedYellow(steps);
}

static struct pixel shadesOfBlueRedYellow(int steps) {
		if (steps == NO_ESCAPE) {
			return getPixel(0,0,0);
		}

		else if (13*steps > 256) {
			return getPixel((256 - 5*steps) % 256, (256-3*steps % 256), (256 - steps) % 256);
		} else {
			return getPixel((steps*13) % 256, 0, 0);
		}
}

static struct pixel getPixel(int red, int green, int blue) {
	struct pixel color = {red, green, blue};
	return color;
}
