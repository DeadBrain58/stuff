#include <stdio.h>
#include <math.h>

#define ERROR 0.000001

double func(double n);

int main(void) {
    double point = 0.35, prev = 0.3, tmp, flag = 0;

    while (fabs(point - prev) > ERROR) {
        tmp = point;

        point = point - ((func(point) * (prev - point)) / (func(prev) - func(point)));

        prev = tmp;

        printf("%f\n", point);
    }

    printf("est: %f\n", point);

    return 0;
}

double func(double n) {
    return tan(n) / (n * n * n) - n * n * n;
}
