#include <stdio.h>

int main(void) {
    float A[3][3] = {
        {3, -1, 14},
        {2, 2, 3},
        {1, -12, -18}
    };
    float B[3] = {7, 0, 33}, X[3] = {0, 0, 0}, key, mult;
    int i, j, k, size = 3;

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

    for (i = 0; i < size; i++) {
        printf("%f ", X[i]);
    }
    printf("\n");

    return 0;
}
