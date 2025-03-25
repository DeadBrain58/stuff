#include <stdio.h>
#include <math.h>

#define ERROR 0.000001

int main(void) {
    int A[3][3] = {
        {3, 1, -2},
        {-1, 4, -3},
        {1, -1, 4}
    };
    int B[3] = {9, -8, 1}, count = 0;
    double x = 1, y = 1, z = 1, prevX, prevY, prevZ;

    do {
        prevX = x;
        prevY = y;
        prevZ = z;

        printf("%f %f %f\n", prevX, prevY, prevZ);

        x = (9 - prevY + 2 * prevZ) / 3;
        y = (-8 + prevX + 3 * prevZ) / 4;
        z = (1 - prevX + prevY) / 4;

        count++;
    } while (fabs(x - prevX) > ERROR || fabs(y - prevY) > ERROR || fabs(z - prevZ) > ERROR);

    printf("est: %f %f %f in %d iterations\n", x, y, z, count);

    return 0;
}
