#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "geometry.h"
#include "material.h"
#include "light.h"
#include "world.h"

WorldObject* newWorldObject(int type, void* geometry, Material* material) {
    WorldObject* wo = malloc(sizeof(WorldObject));
    wo->type = type;
    wo->geometry = geometry;
    wo->material = material;
    return wo;
}

World* newWorld(Color horizonColor, Color zenithColor) {
    World* w = malloc(sizeof(World));
    w->objects = malloc(sizeof(WorldObject) * 100);
    w->numObjects = 0;
    w->lights = malloc(sizeof(Light) * 100);
    w->numLights = 0;
    w->horizonColor = horizonColor;
    w->zenithColor = zenithColor;
    return w;
}

void addObjectToWorld(World* w, WorldObject* wo) {
    w->objects[w->numObjects] = wo;
    w->numObjects++;
}

void addLightToWorld(World* w, Light* l) {
    w->lights[w->numLights] = l;
    w->numLights++;
}

void printWorldObjects(World* w) {
    printf("%d objects in world:\n", w->numObjects);
    for (int i = 0; i < w->numObjects; i++)
    {
        printf("\tObject %d: %d", i, w->objects[i]->type);
    }
}