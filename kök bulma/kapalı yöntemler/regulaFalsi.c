#include <stdio.h>
#include <math.h>

#define ERROR 0.000001

double func(double n);

int main(void) {
    double bot = 2, top = 4, mid = 45, found = 0;

    while (!found && func(mid) > ERROR) {
        mid = (top * func(bot) - bot * func(top)) / (func(bot) - func(top));
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
        printf("est: %f\n", mid);
    }
    else {
        printf("found: %f\n", mid);
    }

    return 0;
}

double func(double n) {
    return tan(n);
}
