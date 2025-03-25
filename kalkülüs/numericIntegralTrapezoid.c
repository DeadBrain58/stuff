#include <stdio.h>

double func(double x);

int main(void) {
    int N = 10, i;
    double area = 0, start = 0, end = 2, width = (end - start) / N;

    for (i = 0; i < N; i++) {
        area += width / 2 * (func(start + i * width) + func(start + (i + 1) * width));
    }

    printf("est: %f\n", area);

    return 0;
}

double func(double x) {
    return x * x / 2;
}
