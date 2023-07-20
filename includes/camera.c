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
Camera newCamera(Vector position, Vector up, Vector right, Vector forward, int width, int height, double fov, double focal_length) {
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
Ray cameraRay(Camera camera, int x, int y) {
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

// Render the scene
Image render(Camera camera, World world, int samples_per_pixel, int max_bounces, float gamma) {

    double antialiasing_correction = 1.0 / (double)samples_per_pixel;

    // Create the image
    Image image = newImage(camera.width, camera.height);
    for (int y = camera.height - 1; y >= 0; y--) {
        for (int x = 0; x < camera.width; x++) {
            // Compute the color with antialiasing
            Ray ray;
            Color color = newColor(0.0, 0.0, 0.0);
            for (int s = 0; s < samples_per_pixel; s++) {
                ray = cameraRay(camera, x, y);
                // Compute the color
                color = addColor(color, rayColor(ray, world, max_bounces));
            }
            color = scaleColor(color, antialiasing_correction);
            color = gammaCorrect(color, gamma);

            // Set the pixel color in the image
            // Need to flip the y-axis
            setPixel(image, x, camera.height - y - 1, color);
        }
    }

    return image;
}