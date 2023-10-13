#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "includes/utils.h"
#include "includes/vector.h"
#include "includes/camera.h"
#include "includes/color.h"
#include "includes/image.h"
#include "includes/geometry.h"
#include "includes/material.h"
#include "includes/light.h"
#include "includes/world.h"

int WIDTH = 1920;
int HEIGHT = 1080;
double PI = 3.14159265359;

int SAMPLES_PER_PIXEL = 70;
int MAX_DEPTH = 10;

double GAMMA = 2.2;

char* OUTPUT_FILE = "output.ppm";

int main(int argc, char *argv[]) {

    // Usage : raytracer [width] [height] [samples per pixel] [max depth] [gamma] [output file]

    if (argc > 1) {
        WIDTH = atoi(argv[1]);
    }

    if (argc > 2) {
        HEIGHT = atoi(argv[2]);
    }

    if (argc > 3) {
        SAMPLES_PER_PIXEL = atoi(argv[3]);
    }

    if (argc > 4) {
        MAX_DEPTH = atoi(argv[4]);
    }

    if (argc > 5) {
        GAMMA = atof(argv[5]);
    }

    if (argc > 6) {
        OUTPUT_FILE = argv[6];
    }

    printf("WIDTH: %d\n", WIDTH);
    printf("HEIGHT: %d\n", HEIGHT);
    printf("SAMPLES_PER_PIXEL: %d\n", SAMPLES_PER_PIXEL);
    printf("MAX_DEPTH: %d\n", MAX_DEPTH);
    printf("GAMMA: %f\n", GAMMA);
    printf("OUTPUT_FILE: %s\n", OUTPUT_FILE);

    srand(time(NULL));

    Vector position = newVector(0, 0, 0);
    Vector up = newVector(0, 1, 0);
    Vector right = newVector(1, 0, 0);
    Vector forward = crossVector(up, right);
    Camera camera = newCamera(position, up, right, forward, WIDTH, HEIGHT, PI / 2.0, 1.0);

    World* world = newWorld(newColor(0.5, 0.7, 1.0), newColor(1.0, 1.0, 1.0));

    Material grey = newMaterial(newColor(0.95, 0.95, 0.95), 0.0, 0.1, 0.9, newColor(0.0, 0.0, 0.0));
    Material white = newMaterial(newColor(1.0, 1.0, 1.0), 0.0, 0.3, 0.9, newColor(0.0, 0.0, 0.0));

    Sphere sphere = newSphere(newVector(0.51, 0, -1), 0.5);
    WorldObject* sphereObject = newWorldObject(SPHERE, &sphere, &grey);
    addObjectToWorld(world, sphereObject);

    Sphere ground = newSphere(newVector(-0.51, 0, -1), 0.5);
    WorldObject* groundObject = newWorldObject(0, &ground, &white);
    addObjectToWorld(world, groundObject);

    Light* light = newLight(newVector(0, 15, -0.5), newColor(1.0, 1.0, 1.0), 1.0);
    addLightToWorld(world, light);

    int nb_threads = get_system_cores();
    
    printf("Rendering with %d threads...\n", nb_threads);

    Image image = renderMultiThreaded(&camera, world, SAMPLES_PER_PIXEL, MAX_DEPTH, 4, nb_threads);
    saveImage(image, OUTPUT_FILE);
    
    printf("Done!\n");
}