#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "vector.h"

// Create a new vector
Vector newVector(double x, double y, double z) {
    Vector v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

// Check if two vectors are equal
bool equalVector(Vector v1, Vector v2) {
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

// Check if a vector is zero
bool isZeroVector(Vector v) {
    return v.x == 0 && v.y == 0 && v.z == 0;
}

// Add two vectors
Vector addVector(Vector v1, Vector v2) {
    Vector v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    return v;
}

// Subtract two vectors
Vector subtractVector(Vector v1, Vector v2) {
    Vector v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    return v;
}

// Multiply a vector by a scalar
Vector scaleVector(Vector v, double s) {
    Vector v2;
    v2.x = v.x * s;
    v2.y = v.y * s;
    v2.z = v.z * s;
    return v2;
}

// Compute the dot product of two vectors
double dotVector(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Compute the cross product of two vectors
Vector crossVector(Vector v1, Vector v2) {
    if (equalVector(v1, v2)) {
        return newVector(0, 0, 0);
    }
    Vector v;
    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return v;
}

// Compute the length of a vector
double lengthVector(Vector v) {
    return sqrt(dotVector(v, v));
}

// Normalize a vector
Vector normalizeVector(Vector v) {
    double length = lengthVector(v);
    if (length == 0) {
        return newVector(0, 0, 0);
    }
    return scaleVector(v, 1 / length);
}

Vector reflectVector(Vector incident_direction, Vector surface_normal) {
    double dot_product = dotVector(incident_direction, surface_normal);
    Vector reflection_direction = subtractVector(incident_direction, scaleVector(surface_normal, 2 * dot_product));
    return reflection_direction;
}

// Print a vector
void printVector(Vector v) {
    printf("<%.2f, %.2f, %.2f>", v.x, v.y, v.z);
}