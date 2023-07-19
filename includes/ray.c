#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "geometry.h"
#include "utils.h"

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
Color rayColor(Ray r, ObjectList ol, int max_bounces) {

    if (max_bounces <= 0) {
        return newColor(0, 0, 0);
    }

    double hit = -1;

    for (int i = 0; i < ol.size; i++) {
        Sphere s = *(Sphere*)ol.objects[i];
        double t = raySphereIntersection(r, s);
        if (t > 0) {
            if (hit < 0) {
                hit = t;
            }
            else {
                hit = fmin(hit, t);
            }
        }
    }

    if (hit > EPSILON) {
        // Bounce the ray
        Vector p = pointAtTime(r, hit);
        Vector target = addVector(p, randomUnitVector());
        Ray bounce = newRay(p, subtractVector(target, p));
        return scaleColor(rayColor(bounce, ol, max_bounces - 1), 2.0/3.0);
    }

    return backgroundColor(r);
}
