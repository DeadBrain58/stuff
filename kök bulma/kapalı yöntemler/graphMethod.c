#include <stdio.h>
#include <math.h>

#define ROOT 2
#define ERR -15

double func(double var);

int main(void) {
    int count = 0, flag = 1;
    double point = 0.0001, delta = 0.01, prevVal, val;

    val = func(point + (delta * count));
    count++;

    while (flag) {
        do {
            prevVal = val;
            val = func(point + (delta * count));
            printf("%.25lf, %.25lf, %.50lf\n", prevVal, val, fabsl(ROOT - point));
            count++;
        } while (prevVal * val > 0);

        if (fabsl(ROOT - point) <= pow(10, ERR)) {
            flag = 0;
        }
        else {
            point = point + (delta * (count - 2));
            count = 0;
            delta /= 2;
            val = prevVal / 2;
        }
    }

    printf("end %.50lf\n", point + (delta * count));

    return 0;
}

double func(double var) {
    return (var * var * var / 4) - 2;
}
