// Assignment 1 Mandelbrot: Pixel coloring functions
// pixelColor.c
//
// Completed by
//  ... (z0000000)
//
// Modified on 2018-??-??
// Tutor's name (dayHH-lab)
//
// Version 1.0.1: Fix issues with spacing and indentation.
// Version 1.0.0: Assignment released.

#include "mandelbrot.h"
#include "pixelColor.h"

// This function should take a number (of steps taken to escape the
// Mandelbrot set), and convert it to a color.
//
// You have artistic licence here, so make your Mandelbrot look amazing.
struct pixel pixelColor(int steps) {
    struct pixel color = {
        .red = steps,
        .green = steps,
        .blue = steps,
    };

    // TODO: Change the color of the pixel for different numbers of
    // steps.

    return color;
}
