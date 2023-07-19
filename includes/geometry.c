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