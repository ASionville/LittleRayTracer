# Little Raytracer

This is a little raytracer I wrote in C to learn more about ray tracing and to put my coding and algebra skills to the test. It is based on the beginning of the book [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by Peter Shirley.

## Features

- [x] Spheres
- [x] Lambertian materials
- [ ] Metal materials
- [ ] Dielectric materials
- [x] Lights
- [x] Shadows
- [x] Anti-aliasing
- [x] Diffuse materials
- [x] Camera
- [x] Depth of field
- [x] Gamma correction
- [x] Multi-threading

## Usage
- Compile all files : `gcc -o raytracer main.c includes/*.c;`
- Run the program : `./raytracer [width] [height] [samples] [max_depth] [gamma] [output_file]`
- Example : `./raytracer 800 600 100 50 2.2 image.ppm`

## Modify the scene

Every object in the scene is defined in `main.c` as follows :

### Vectors
Vectors are to be defined using `newVector(x, y, z)`.

### Colors
Colors are to be defined using `newColor(r, g, b)`.

### Camera
The camera is defined using `newCamera(position, up, right, forward, width, height, fov, focal_length)`.

### World
The world in itself contains the color gradient of the sky.
It is defined using `newWorld(HorizonColor, SkyColor)`.

### Materials
Materials define the way light interacts with objects.
They are defined using `newMaterial(Color, metallic, roughness, reflectivity, emission)`

### Spheres
Spheres only contain geometrical data.
They are defined using `newSphere(position, radius)`.

### World objects
The program uses a list of `WorldObject` to store all the objects in the scene.
To create a new object, use `newWorldObject(type, sphere, material)`.
To add an object to the world, use `addObject(world, object)`.

### Lights
A light is needed to illuminate the scene.
The program uses a list of `Light` to store all the lights in the scene.
To create a new light, use `newLight(position, color, intensity)`.
To add a light to the world, use `addLightToWorld(world, light)`.