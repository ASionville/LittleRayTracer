#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector.h"

typedef struct
{
    void** objects;
    int size;
} ObjectList;

typedef struct
{
    Vector center;
    double radius;
} Sphere;

Sphere newSphere(Vector center, double radius);

ObjectList newObjectList();
void addObject(ObjectList* ol, void* object);

#endif // !GEOMETRY_H