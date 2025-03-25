#include <stdio.h>
#include <math.h>

#define ERROR 0.000001

double g(double x);

int main(void) {
    double point = 1, curr, prev;

    curr = g(point);

    do {
        prev = curr;
        curr = g(curr);

        printf("%f %f\n", curr, prev);
    } while (fabs(curr - prev) > ERROR);

    printf("est: %f\n", curr);

    return 0;
}

double g(double x) {
    return 1 - sin(x);
}
