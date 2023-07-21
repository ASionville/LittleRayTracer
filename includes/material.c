#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "color.h"
#include "material.h"

// Create a new material
Material newMaterial(Color color, double metallic, double roughness, double reflectivity, Color emission)
{
    Material m;
    m.color = color;
    m.metallic = metallic;
    m.roughness = roughness;
    m.reflectivity = reflectivity;
    m.emission = emission;
    return m;
}