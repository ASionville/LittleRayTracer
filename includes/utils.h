#ifndef UTILS_H
#define UTILS_H
#include "vector.h"

#define EPSILON 0.000001

double randomRange(double min, double max);
double clamp(double x, double min, double max);

Vector randomVector();
Vector randomVectorRange(double min, double max);
Vector randomInUnitSphere();
Vector randomUnitVector();

int get_system_cores();

#endif // !UTILS_H