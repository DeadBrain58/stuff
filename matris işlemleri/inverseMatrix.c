#include <stdio.h>
#include <math.h>

int main(void) {
    int size = 3, i, j, k;
    float key, mult;
    float mtr[3][3] = {
        {1, 2, 3}, 
        {4, 5, 6}, 
        {7, 8, 10}
    };
    float unit[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    for (i = 0; i < size; i++) {
        key = mtr[i][i];

        for (j = 0; j < size; j++) {
            mtr[i][j] /= key;
            unit[i][j] /= key;
        }

        for (k = i + 1; k < size; k++) {
            mult = mtr[k][i];
            for (j = 0; j < size; j++) {
                mtr[k][j] -= mult * mtr[i][j];
                unit[k][j] -= mult * unit[i][j];
            }
        }
    }

    for (i = size - 1; i >= 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            mult = mtr[j][i];
            for (k = 0; k < size; k++) {
                mtr[j][k] -= mult * mtr[i][k];
                unit[j][k] -= mult * unit[i][k];
            }
        }
    }

    for(i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%f ", unit[i][j]);
        }
        printf("\n");
    }

    return 0;
}
