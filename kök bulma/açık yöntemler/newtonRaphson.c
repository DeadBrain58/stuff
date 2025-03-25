#include <stdio.h>
#include <math.h>

#define ERROR 0.000001

double func(double n);
double deriv(double n);

int main(void) {
    double point = -2, prev = 0;

    while (fabs(point - prev) > ERROR) {
        prev = point;

        point = point - func(point) / deriv(point);

        printf("%f\n", point);
    }

    printf("est: %f\n", point);

    return 0;
}

double func(double n) {
    return sin(n) - 3 * n + 6;
}

double deriv(double n) {
    return cos(n) - 3;
}
