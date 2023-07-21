#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "vector.h"
#include "color.h"
#include "light.h"

Light *newLight(Vector position, Color color, double intensity)
{
    Light *l = malloc(sizeof(Light));
    l->position = position;
    l->color = color;
    l->intensity = intensity;
    return l;
}