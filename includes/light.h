#ifndef LIGHT_H
#define LIGHT_H
#include "vector.h"
#include "color.h"

typedef struct {
    Vector position;
    Color color;
    double intensity;
} Light;

Light* newLight(Vector position, Color color, double intensity);

#endif // !LIGHT_H