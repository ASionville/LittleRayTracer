#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "geometry.h"
#include "material.h"
#include "light.h"
#include "world.h"
#include "utils.h"

// Create a new ray
Ray newRay(Vector origin, Vector direction)
{
    Ray ray;
    ray.origin = origin;
    ray.direction = direction;
    return ray;
}

// Point on ray at time t
Vector pointAtTime(Ray ray, double t)
{
    return addVector(ray.origin, scaleVector(ray.direction, t));
}

// Compute the intersection of a ray and a sphere (returns -1 if no intersection, otherwise returns t)
double raySphereIntersection(Ray ray, Sphere sphere)
{
    Vector oc = subtractVector(ray.origin, sphere.center);
    double a = pow(lengthVector(ray.direction), 2);
    double b = dotVector(oc, ray.direction);
    double c = pow(lengthVector(oc), 2) - pow(sphere.radius, 2);
    double discriminant = b * b - a * c;

    if (discriminant < 0)
    {
        return -1;
    }
    else
    {
        return (-b - sqrt(discriminant)) / a;
    }
}

// Get background color
Color backgroundColor(Ray ray, World world)
{
    Vector unit_direction = normalizeVector(ray.direction);
    double background_lerp_factor = 0.5 * (unit_direction.y + 1.0);
    return lerpColor(world.horizonColor, world.zenithColor, background_lerp_factor);
}

WorldObject *getClosestHit(Ray ray, World world, double *closestHit)
{
    // Returns the object and the distance if there is a hit, otherwise returns NULL
    // Also returns the distance to the closest hit via the closestHit pointer

    WorldObject *obj = NULL;
    WorldObject *closestObject = NULL;
    *closestHit = -1;

    for (int i = 0; i < world.numObjects; i++)
    {
        obj = world.objects[i];
        double currentHit = -1;

        switch (obj->type)
        {
        case SPHERE:
            currentHit = raySphereIntersection(ray, *(Sphere *)obj->geometry);
            break;
        default:
            break;
        }
        if (currentHit > 0)
        {
            if (*closestHit < 0)
            {
                *closestHit = currentHit;
                closestObject = obj;
            }
            else
            {
                if (currentHit < *closestHit)
                {
                    *closestHit = currentHit;
                    closestObject = obj;
                }
            }
        }
    }
    return closestObject;
}

Color computeDirectIllumination(Ray ray, World world, WorldObject obj, Vector point, Vector normal)
{
    Color direct_color = newColor(0, 0, 0);
    Light light;

    // Go trough all lights (all lights are point lights for now)
    for (int i = 0; i < world.numLights; i++)
    {
        light = *(world.lights[i]);
        Vector to_light = subtractVector(light.position, point);
        Vector light_direction = normalizeVector(to_light);
        double light_distance = lengthVector(to_light);

        // Check if the light is visible
        Ray shadow_ray = newRay(point, light_direction);
        double shadow_hit = -1;
        WorldObject* shadow_object = getClosestHit(shadow_ray, world, &shadow_hit);

        if (shadow_object == NULL || shadow_hit > light_distance)
        {
            // Diffuse lighting
            Color diffuse_color = newColor(0, 0, 0);
            double diffuse_factor = dotVector(light_direction, normal);
            if (diffuse_factor > 0)
            {
                diffuse_color = scaleColor(light.color, diffuse_factor);
            }

            // Specular lighting (Phong model)
            Color specular_color = newColor(0, 0, 0);
            Vector reflection = reflectVector(light_direction, normal);
            double r_dot_v = dotVector(reflection, normalizeVector(ray.direction));
            if (r_dot_v > 0)
            {
                double specular_factor = pow(r_dot_v, obj.material->roughness);
                specular_color = scaleColor(light.color, specular_factor);
            }

            // Compute the direct illumination
            Color light_color = addColor(diffuse_color, specular_color);
            direct_color = addColor(direct_color, light_color);

        }
    }
    return direct_color;
}

// Compute the color of a ray
Color rayColor(Ray ray, World world, int max_bounces)
{
    // If we've reached the maximum number of bounces, return black
    if (max_bounces <= 0)
    {
        return newColor(0, 0, 0);
    }
    
    double hit = -1;
    WorldObject *closestObject = getClosestHit(ray, world, &hit);
    if (closestObject != NULL)
    {
        Vector hitPoint;
        Vector normal;
        switch (closestObject->type)
        {
        case SPHERE:
            hitPoint = pointAtTime(ray, hit);
            normal = getSphereLocalNormal(*(Sphere*)(closestObject->geometry), hitPoint);

        default:
            break;
        }

        // Compute the direct illumination
        Color direct_color = computeDirectIllumination(ray, world, *closestObject, hitPoint, normal);
        return direct_color;
    }

    return backgroundColor(ray, world);
}
