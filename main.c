#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "includes/vector.h"
#include "includes/camera.h"
#include "includes/image.h"

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

    ObjectList ol = newObjectList();
    Sphere s1 = newSphere(newVector(0, 0, -1), 0.5);
    addObject(&ol, &s1);
    Sphere ground = newSphere(newVector(0, -100.5, -1), 100);
    addObject(&ol, &ground);

    Image image = render(camera, ol, SAMPLES_PER_PIXEL, MAX_DEPTH, GAMMA);
    saveImage(image, "test.ppm");
    printf("Done!\n");
}