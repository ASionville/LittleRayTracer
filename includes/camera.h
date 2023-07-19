#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "ray.h"
#include "image.h"

typedef struct
{
    Vector position;
    Vector up;
    Vector right;
    Vector forward;
    int width;
    int height;
    double fov;
    double focal_length;
} Camera;

Camera newCamera(Vector position, Vector up, Vector right, Vector forward, int width, int height, double fov, double focal_length);
Ray cameraRay(Camera camera, int x, int y); 

Image render(Camera camera, ObjectList ol, int samples_per_pixel);

#endif // !CAMERA_H