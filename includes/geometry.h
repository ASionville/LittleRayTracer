#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector.h"

typedef struct
{
    Vector center;
    double radius;
} Sphere;

Sphere newSphere(Vector center, double radius);
Vector getSphereLocalNormal(Sphere sphere, Vector point);

#endif // !GEOMETRY_H