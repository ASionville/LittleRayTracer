#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "includes/vector.h"
#include "includes/camera.h"
#include "includes/image.h"
#include "includes/geometry.h"
#include "includes/material.h"
#include "includes/light.h"
#include "includes/world.h"

#define WIDTH 500
#define HEIGHT 400
#define PI 3.14159265359

#define SAMPLES_PER_PIXEL 50
#define MAX_DEPTH 50

#define GAMMA 2.0

int main(int argc, char *argv[]) {

    srand(time(NULL));

    Vector position = newVector(0, 0, 0);
    Vector up = newVector(0, 1, 0);
    Vector right = newVector(1, 0, 0);
    Vector forward = crossVector(up, right);
    Camera camera = newCamera(position, up, right, forward, WIDTH, HEIGHT, PI / 2.0, 1.0);

    World* world = newWorld(newColor(0.5, 0.7, 1.0), newColor(1.0, 1.0, 1.0));

    Material white = newMaterial(newColor(0.8, 0.8, 0.8), 0.0, 0.0, 0.0, newColor(0.0, 0.0, 0.0));
    Sphere sphere = newSphere(newVector(0, 0, -1), 0.5);
    WorldObject* sphereObject = newWorldObject(SPHERE, &sphere, &white);
    addObjectToWorld(world, sphereObject);

    Sphere ground = newSphere(newVector(0, -100.5, -1), 100);
    WorldObject* groundObject = newWorldObject(0, &ground, &white);
    addObjectToWorld(world, groundObject);

    Light* light = newLight(newVector(0, 1, -0.3), newColor(1.0, 1.0, 1.0), 0.8);
    addLightToWorld(world, light);

    Image image = render(camera, *world, SAMPLES_PER_PIXEL, MAX_DEPTH, GAMMA);
    saveImage(image, "test.ppm");
    printf("Done!\n");
}