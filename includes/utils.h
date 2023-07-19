#ifndef UTILS_H
#define UTILS_H

#define EPSILON 0.000001

double randomRange(double min, double max);
double clamp(double x, double min, double max);

Vector randomVector();
Vector randomVectorRange(double min, double max);

#endif // !UTILS_H