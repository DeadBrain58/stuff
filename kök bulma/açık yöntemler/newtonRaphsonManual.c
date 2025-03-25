#include <stdio.h>
#include <math.h>

#define ERROR 0.000001

double func(double n);
double deriv(double n, double dx);

int main(void) {
    double point = -2, prev = 0, dx = 0.001;

    while (fabs(point - prev) > ERROR) {
        prev = point;

        point = point - func(point) / deriv(point, dx);

        printf("%f\n", point);
    }

    printf("est: %f\n", point);

    return 0;
}

double func(double n) {
    return sin(n) - 3 * n + 6;
}

double deriv(double n, double dx) {
    return (func(n + dx) - func(n - dx)) / (2 * dx);
}
