#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "geometry.h"
#include "camera.h"

// Create a new camera
Camera newCamera(Vector position, Vector up, Vector right, Vector forward, int width, int height, double fov) {
    Camera c;
    c.position = position;
    c.up = up;
    c.right = right;
    c.forward = forward;
    c.width = width;
    c.height = height;
    c.fov = fov;
    return c;
}

// Compute the ray for a given pixel
Ray cameraRay(Camera camera, int x, int y) {
    // Compute the aspect ratio
    double aspectRatio = (double)camera.width / (double)camera.height;

    // Compute the pixel coordinates
    double px = (2.0 * ((x + 0.5) / camera.width) - 1.0) * aspectRatio * tan(camera.fov / 2.0);
    double py = (1.0 - 2.0 * ((y + 0.5) / camera.height)) * tan(camera.fov / 2.0);

    // Compute the direction
    Vector direction = addVector(camera.forward, addVector(scaleVector(camera.right, px), scaleVector(camera.up, py)));
    direction = normalizeVector(direction);

    // Create the ray
    Ray ray = newRay(camera.position, direction);

    return ray;
}

// Render the scene
Image render(Camera camera) {
    // Create the image
    Image image = newImage(camera.width, camera.height);

    for (int y = camera.height - 1; y >= 0; y--) {
        for (int x = 0; x < camera.width; x++) {
            // Compute the ray for the current pixel
            Ray ray = cameraRay(camera, x, y);

            // Compute the color for the current ray
            Color color = rayColor(ray);

            // Set the pixel color in the image
            setPixel(image, x, y, color);
        }
    }

    return image;
}