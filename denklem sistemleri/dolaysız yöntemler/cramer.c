#include <stdio.h>
#include <stdlib.h>

float determinant(float** mtr, int size);
float* cramer(float** coeff, float* cons, int size);

int main(void) {
    float **A, *B, *X;
    int size, i, j;

    printf("Matrisin boyutu: ");
    scanf("%d", &size);

    // Katsayı matrisi için yer açma
    A = (float**) malloc(size * sizeof(float*));
    for (i = 0; i < size; i++) {
        *(A + i) = (float*) malloc(size * sizeof(float));
    }

    // Değer matrisi için yer açma
    B = (float*) malloc(size * sizeof(float));

    printf("Katsayi matrisinin degerleri: \n");
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            scanf("%f", *(A + i) + j);
        }
    }

    printf("\nDeger matrisinin degerleri: \n");
    for (i = 0; i < size; i++) {
        scanf("%f", B + i);
    }

    // Hesaplamanın yapıldığı yer
    if (determinant(A, size)) {
        X = cramer(A, B, size);

        printf("\nCozumler: \n");
        for (i = 0; i < size; i++) {
            printf("%f ", *(X + i));
        }
        printf("\n");
    } 
    else {
        printf("Cozum yok!\n");
    }

    // Hafızayı boşaltma
    for (i = 0; i < size; i++) {
        free(*(A + i));
    }

    free(A);
    free(B);
    free(X);

    return 0;
}

// Determinantı Laplace açılımı ile bulan fonksiyon
float determinant(float** mtr, int size) {
    float **copy, **minor;
    int i, j, k;
    float det = 0, tempDet;

    if (size == 1) {
        return *(*(mtr));
    }

    // Matrisin kopyasını oluşturma
    copy = (float**) malloc(size * sizeof(float*));
    for (i = 0; i < size; i++) {
        *(copy + i) = (float*) malloc(size * sizeof(float));
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            *(*(copy + i) + j) = *(*(mtr + i) + j);
        }
    }

    // Minör matrisi için yer açma
    minor = (float**) malloc((size - 1) * sizeof(float*));
    for (i = 0; i < size - 1; i++) {
        *(minor + i) = (float*) malloc((size - 1) * sizeof(float));
    }

    // İlk satır için Laplace açılımı
    for (i = 0; i < size; i++) {
        // Minör matrisi oluşturma, önce sol sonra sağ taraf
        for (j = 1; j < size; j++) {
            for (k = 0; k < i; k++) {
                *(*(minor + j - 1) + k) = *(*(mtr + j) + k);
            }
            for (k = i + 1; k < size; k++) {
                *(*(minor + j - 1) + k - 1) = *(*(mtr + j) + k);
            }
        }

        // Minörün determinantını bulma
        tempDet = determinant(minor, size - 1);
        
        // Determinantı hesaplama
        det += (i & 1 ? -1 : 1) * (*(*(mtr + 0) + i) * tempDet); 

        /*
            Not
            (i & 1 ? -1 : 1) =

            if (i & 1) {
                -1 * (*(*(mtr + 0) + i) * tempDet);
            }
            else {
                1 * (*(*(mtr + 0) + i) * tempDet);
            }

            i'yi 1 ile AND yaparak sütun sayısının tek mi çift mi olduğunu buluyoruz
            i = 0, i & 1 = 0
            i = 1, i & 1 = 1
            i = 2, i & 1 = 0 (binary'de 2: 10)
        */
    }
    
    free(minor);
    return det;
}

// Cramer yöntemi
float* cramer(float** coeff, float* cons, int size) {
    int i, j;
    float det;
    float *X, **copy;

    // Matrisin kopyasını oluşturma
    copy = (float**) malloc(size * sizeof(float*));
    for (i = 0; i < size; i++) {
        *(copy + i) = (float*) malloc(size * sizeof(float));
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            *(*(copy + i) + j) = *(*(coeff + i) + j);
        }
    }

    // Çözüm matrisi için yer açma
    for (i = 0; i < size; i++) {
        X = (float*) malloc(size * sizeof(float));
    }

    det = determinant(copy, size);

    // Sütunları değiştirip değişkeni bulma
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            *(*(copy + j) + i) = *(cons + j);
        }

        *(X + i) = determinant(copy, size) / det;

        // Sütunu eski haline getirme
        for (j = 0; j < size; j++) {
            *(*(copy + j) + i) = *(*(coeff + j) + i);
        }
    }

    // Hafızayı boşaltma
    for (i = 0; i < size; i++) {
        free(*(copy + i));
    }
    free(copy);

    return X;
}
