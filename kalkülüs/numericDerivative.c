#include <stdio.h>
#include <math.h>

double func(double x);

int main(void) {
    double dx = 0.001, point = 1;
    
    double geri = (func(point) - func(point - dx)) / dx; 
    double ileri = (func(point + dx) - func(point)) / dx; 
    double merkezi = (func(point + dx) - func(point - dx)) / 2 / dx;

    printf("%f %f %f\n", geri, ileri, merkezi);

    return 0;
}

double func(double x) {
    return sin(x) / atan(x) / sqrt(x);
}
