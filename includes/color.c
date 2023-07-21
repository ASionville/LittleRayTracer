#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "color.h"

// Create a new color
Color newColor(double r, double g, double b)
{
    Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}

// Check if two colors are equal
bool equalColor(Color c1, Color c2)
{
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

// Add two colors
Color addColor(Color c1, Color c2)
{
    Color c;
    c.r = c1.r + c2.r;
    c.g = c1.g + c2.g;
    c.b = c1.b + c2.b;
    return c;
}

// Subtract two colors
Color subtractColor(Color c1, Color c2)
{
    Color c;
    c.r = c1.r - c2.r;
    c.g = c1.g - c2.g;
    c.b = c1.b - c2.b;
    return c;
}

// Multiply two colors
Color mulColor(Color c1, Color c2)
{
    Color c;
    c.r = c1.r * c2.r;
    c.g = c1.g * c2.g;
    c.b = c1.b * c2.b;
    return c;
}

// Multiply a color by a scalar
Color scaleColor(Color c, double s)
{
    Color c2;
    c2.r = c.r * s;
    c2.g = c.g * s;
    c2.b = c.b * s;
    return c2;
}

// Lerp between two colors
Color lerpColor(Color c1, Color c2, double t)
{
    Color c;
    c.r = c1.r + (c2.r - c1.r) * t;
    c.g = c1.g + (c2.g - c1.g) * t;
    c.b = c1.b + (c2.b - c1.b) * t;
    return c;
}

Color gammaCorrect(Color c, float gamma)
{
    Color c2;
    c2.r = pow(c.r, gamma);
    c2.g = pow(c.g, gamma);
    c2.b = pow(c.b, gamma);
    return c2;
}

// Print a color
void printColor(Color c)
{
    printf("(%f, %f, %f)\n", c.r, c.g, c.b);
}