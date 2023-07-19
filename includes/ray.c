#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "geometry.h"

// Create a new ray
Ray newRay(Vector origin, Vector direction) {
    Ray r;
    r.origin = origin;
    r.direction = direction;
    return r;
}

// Point on ray at time t
Vector pointAtTime(Ray r, double t) {
    return addVector(r.origin, scaleVector(r.direction, t));
}

// Compute the intersection of a ray and a sphere (returns -1 if no intersection, otherwise returns t)
double raySphereIntersection(Ray ray, Sphere sphere) {
    Vector oc = subtractVector(ray.origin, sphere.center);
    double a = pow(lengthVector(ray.direction), 2);
    double b = dotVector(oc, ray.direction);
    double c = pow(lengthVector(oc), 2) - pow(sphere.radius, 2);
    double discriminant = b * b - a * c;

    if (discriminant < 0) {
        return -1;
    }
    else {
        return (-b - sqrt(discriminant)) / a;
    }
}

// Get background color
Color backgroundColor(Ray r) {
    Vector unit_direction = normalizeVector(r.direction);
    double background_lerp_factor = 0.5 * (unit_direction.y + 1.0);
    Color c1 = newColor(0.5, 0.7, 1.0);
    Color c2 = newColor(1.0, 1.0, 1.0);
    return lerpColor(c1, c2, background_lerp_factor);
}


// Compute the color of a ray
Color rayColor(Ray r) {
    Sphere sphere = newSphere(newVector(0, 0, -1), 0.5);
    double hit = raySphereIntersection(r, sphere);

    if (hit > 0) {
        Vector normal = normalizeVector(subtractVector(pointAtTime(r, hit), sphere.center));
        Color c1 = newColor(normal.x + 1, normal.y + 1, normal.z + 1);
        return scaleColor(c1, 0.5);
    }
    return backgroundColor(r);
}