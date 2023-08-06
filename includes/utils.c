#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"

#define PI 3.14159265359

double random()
{
    return (double)rand() / (double)RAND_MAX;
}

double randomRange(double min, double max)
{
    return min + (max - min) * random();
}

double clamp(double x, double min, double max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

Vector randomVector()
{
    return newVector(random(), random(), random());
}

Vector randomVectorRange(double min, double max)
{
    return newVector(randomRange(min, max), randomRange(min, max), randomRange(min, max));
}

Vector randomInUnitSphere()
{
    while (true)
    {
        Vector p = randomVectorRange(-1, 1);
        if (lengthVector(p) >= 1)
            continue;
        return p;
    }
}

Vector randomUnitVector()
{
    return normalizeVector(randomVector());
}

int get_system_cores()
{
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
}