#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

// PBR material
typedef struct Material {
    Color color;
    double metallic;
    double roughness;
    double reflectivity;
    Color emission;
} Material;

Material newMaterial(Color color, double metallic, double roughness, double reflectivity, Color emission);

#endif // !MATERIAL_H