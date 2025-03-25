#include <stdio.h>
#include <math.h>

#define ERROR 0.000001

double func(double n);

int main(void) {
    double bot = -2, top = 0.68, mid, found = 0;

    while (!found && fabs(top - bot) > ERROR) {
        mid = (bot + top) / 2;
        printf("mid %f\n", mid);

        if (func(bot) * func(mid) < 0) {
            top = mid;
        }
        else if (func(top) * func(mid) < 0) {
            bot = mid;
        }
        else {
            found = 1;
        }

        printf("%f %f\n", bot, top);
    }

    if (!found) {
        printf("est: %f\n", (top + bot) / 2);
    }
    else {
        printf("found: %f\n", mid);
    }

    return 0;
}

double func(double n) {
    return n * n + sin(3 * n) - 2;
}
