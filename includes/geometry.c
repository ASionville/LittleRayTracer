#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "vector.h"
#include "geometry.h"

// Create a new sphere
Sphere newSphere(Vector center, double radius) {
    Sphere s;
    s.center = center;
    s.radius = radius;
    return s;
}

// Create a new object list
ObjectList newObjectList() {
    ObjectList ol;
    ol.objects = malloc(0);
    ol.size = 0;
    return ol;
}

// Add an object to the object list
void addObject(ObjectList* ol, void* object) {
    ol->size++;
    ol->objects = realloc(ol->objects, ol->size * sizeof(void*));
    ol->objects[ol->size - 1] = object;
}