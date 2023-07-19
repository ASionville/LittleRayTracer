#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector.h"

typedef struct
{
    Vector center;
    double radius;
} Sphere;

Sphere newSphere(Vector center, double radius);

#endif // !GEOMETRY_H