#ifndef CAMERA_H
#define CAMERA_H

#include <windows.h>
#include "vector.h"
#include "ray.h"
#include "image.h"
#include "world.h"

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

typedef struct
{
    Camera *camera;
    World *world;
    int samples_per_pixel;
    int max_bounces;
    float gamma;
    int start_y;
    int end_y;
    Image *image;
} ThreadData;

Camera newCamera(Vector position, Vector up, Vector right, Vector forward, int width, int height, double fov, double focal_length);
Ray cameraRay(Camera camera, int x, int y); 

DWORD WINAPI renderThread(LPVOID lpParam);
Image renderMultiThreaded(Camera *camera, World *world, int samples_per_pixel, int max_bounces, float gamma, int num_threads);

#endif // !CAMERA_H