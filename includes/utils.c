#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

double randomDouble() {
    return (double)rand() / (double)RAND_MAX;
}

double randomDoubleRange(double min, double max) {
    return min + (max - min) * randomDouble();
}

