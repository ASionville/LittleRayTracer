#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    double x;
    double y;
    double z;
} Vector;

Vector newVector(double x, double y, double z);

bool equalVector(Vector v1, Vector v2);
bool isZeroVector(Vector v);

Vector addVector(Vector v1, Vector v2);
Vector subtractVector(Vector v1, Vector v2);
Vector scaleVector(Vector v, double s);

double dotVector(Vector v1, Vector v2);
Vector crossVector(Vector v1, Vector v2);

double lengthVector(Vector v);
Vector normalizeVector(Vector v);

void printVector(Vector v);

#endif