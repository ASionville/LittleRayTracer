#ifndef WORLD_H
#define WORLD_H

#include "color.h"
#include "geometry.h"
#include "material.h"
#include "light.h"

#define SPHERE 0

typedef struct 
{
    int type;
    void* geometry;
    Material* material;
} WorldObject;

typedef struct
{
    WorldObject** objects;
    int numObjects;
    Light** lights;
    int numLights;
    Color horizonColor;
    Color zenithColor;
} World;

WorldObject* newWorldObject(int type, void* geometry, Material* material);

World* newWorld();
void addObjectToWorld(World* world, WorldObject* object);
void addLightToWorld(World* world, Light* light);

void printWorldObjects(World* world);

#endif // !WORLD_H