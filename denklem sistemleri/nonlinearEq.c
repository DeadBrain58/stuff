// x^2 + y = 3
// x + y^2 = 5

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERROR 0.0001

double* eliminationMethod(double A[][2], double B[], int size);
double f(double x, double y);
double fx(double x, double y);
double fy(double x, double y);
double g(double x, double y);
double gx(double x, double y);
double gy(double x, double y);

int main(void) {
    int count = 0;
    double x = 0.7, y = 1.7, diffX, diffY;
    double* X = (double*) malloc(2 * sizeof(double));
    double A[2][2], B[2];
    
    do {
        printf("%f %f\n", x, y);

        A[0][0] = fx(x, y);
        A[0][1] = fy(x, y);
        A[1][0] = gx(x, y);
        A[1][1] = gy(x, y);

        B[0] = -f(x, y);
        B[1] = -g(x, y);

        X = eliminationMethod(A, B, 2);

        diffX = X[0];
        diffY = X[1];

        x += diffX;
        y += diffY;
        count++;
    } while (fabs(diffX) > ERROR || fabs(diffY) > ERROR);

    printf("est: %f %f in %d iterations\n", x, y, count);
    
    return 0;
}

double* eliminationMethod(double A[][2], double B[], int size) {
    int i, j, k;
    double key, mult;
    double* X = (double*) malloc(size * sizeof(double));

    for (i = 0; i < size; i++) {
        key = A[i][i];
        B[i] /= key;

        for (j = 0; j < size; j++) {
            A[i][j] /= key;
        }

        for (k = i + 1; k < size; k++) {
            mult = A[k][i];
            B[k] -= mult * B[i];
            for (j = 0; j < size; j++) {
                A[k][j] -= mult * A[i][j];
            }
        }
    }

    for (i = size - 1; i >= 0; i--) {
        key = 0;
        for (j = i + 1; j < size; j++) {
            key += A[i][j] * X[j];
        }

        X[i] = B[i] - key;
    }

    return X;
}

double f(double x, double y) {
    return x * x + y - 3;
}

double fx(double x, double y) {
    return 2 * x;
}

double fy(double x, double y) {
    return 1;
}

double g(double x, double y) {
    return x + y * y - 5;
}

double gx(double x, double y) {
    return 1;
}

double gy(double x, double y) {
    return 2 * y;
}
