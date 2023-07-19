#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "includes/vector.h"
#include "includes/camera.h"
#include "includes/image.h"

int main(int argc, char *argv[]) {
    Vector position = newVector(0, 0, 0);
    Vector up = newVector(0, 1, 0);
    Vector right = newVector(1, 0, 0);
    Vector forward = crossVector(up, right);
    Camera camera = newCamera(position, up, right, forward, 800, 600, 3.14159265359 / 2.0);

    Image image = render(camera);
    saveImage(image, "image.ppm");
    printf("Done!\n");
}