#ifndef RAY_H
#define RAY_H
#include "vector.h"
#include "color.h"
#include "geometry.h"

typedef struct {
    Vector origin;
    Vector direction;
} Ray;

Ray newRay(Vector origin, Vector direction);
Vector rayPointAt(Ray ray, double t);
double raySphereIntersection(Ray ray, Sphere sphere);

Color rayColor(Ray ray, ObjectList ol, int max_bounces);

#endif // !RAY_H