#ifndef COLOR_H
#define COLOR_H

typedef struct {
    double r;
    double g;
    double b;
} Color;

Color newColor(double r, double g, double b);

bool equalColor(Color c1, Color c2);

Color addColor(Color c1, Color c2);
Color subColor(Color c1, Color c2);

Color mulColor(Color c1, Color c2);

Color scaleColor(Color c, double s);
Color lerpColor(Color c1, Color c2, double t);

Color gammaCorrect(Color c, float gamma);

void printColor(Color c);

#endif // !COLOR_H