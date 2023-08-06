#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "geometry.h"
#include "camera.h"
#include "world.h"
#include "image.h"
#include "utils.h"

// Create a new camera
Camera newCamera(Vector position, Vector up, Vector right, Vector forward, int width, int height, double fov, double focal_length)
{
    Camera c;
    c.position = position;
    c.up = up;
    c.right = right;
    c.forward = forward;
    c.width = width;
    c.height = height;
    c.fov = fov;
    c.focal_length = focal_length;
    return c;
}

// Compute the ray for a given pixel
Ray cameraRay(Camera camera, int x, int y)
{
    // Compute the aspect ratio
    double aspectRatio = (double)camera.width / (double)camera.height;

    double rx = randomRange(-0.7, 0.7);
    double ry = randomRange(-0.7, 0.7);

    double x_with_offset = (double)x + rx;
    double y_with_offset = (double)y + ry;

    // Compute the pixel coordinates
    double px = (2.0 * ((x_with_offset + 0.5) / camera.width) - 1.0) * aspectRatio * tan(camera.fov / 2.0);
    double py = (1.0 - 2.0 * ((y_with_offset + 0.5) / camera.height)) * tan(camera.fov / 2.0);

    // Compute the direction
    Vector direction = addVector(camera.forward, addVector(scaleVector(camera.right, px), scaleVector(camera.up, py)));
    direction = normalizeVector(direction);

    // Create the ray
    Ray ray = newRay(camera.position, direction);

    return ray;
}

DWORD WINAPI renderThread(LPVOID lpParam)
{
    ThreadData *data = (ThreadData *)lpParam;

    double antialiasing_correction = 1.0 / (double)data->samples_per_pixel;

    for (int y = data->end_y - 1; y >= data->start_y; y--)
    {
        for (int x = 0; x < data->camera->width; x++)
        {
            // Compute the color with antialiasing
            Ray ray;
            Color color = newColor(0.0, 0.0, 0.0);
            for (int s = 0; s < data->samples_per_pixel; s++)
            {
                ray = cameraRay(*data->camera, x, y);
                // Compute the color
                color = addColor(color, rayColor(ray, *data->world, data->max_bounces));
            }
            color = scaleColor(color, antialiasing_correction);
            color = gammaCorrect(color, data->gamma);

            // Set the pixel color in the image
            // Need to flip the y-axis
            setPixel(*data->image, x, data->camera->height - y - 1, color);
        }
    }

    return 0;
}

Image renderMultiThreaded(Camera *camera, World *world, int samples_per_pixel, int max_bounces, float gamma, int num_threads)
{
    Image image = newImage(camera->width, camera->height);
    HANDLE *threadHandles = malloc(num_threads * sizeof(HANDLE));
    ThreadData *threadDataArray = malloc(num_threads * sizeof(ThreadData));

    int rows_per_thread = camera->height / num_threads;
    int remaining_rows = camera->height % num_threads;
    int start_y = 0;

    for (int i = 0; i < num_threads; i++)
    {
        int end_y = start_y + rows_per_thread;
        if (i == num_threads - 1)
            end_y += remaining_rows;

        threadDataArray[i].camera = camera;
        threadDataArray[i].world = world;
        threadDataArray[i].samples_per_pixel = samples_per_pixel;
        threadDataArray[i].max_bounces = max_bounces;
        threadDataArray[i].gamma = gamma;
        threadDataArray[i].start_y = start_y;
        threadDataArray[i].end_y = end_y;
        threadDataArray[i].image = &image;

        threadHandles[i] = CreateThread(NULL, 0, renderThread, &threadDataArray[i], 0, NULL);

        start_y = end_y;
    }

    WaitForMultipleObjects(num_threads, threadHandles, TRUE, INFINITE);

    for (int i = 0; i < num_threads; i++)
    {
        CloseHandle(threadHandles[i]);
    }

    free(threadHandles);
    free(threadDataArray);

    return image;
}