#include <stdio.h>

#define SIZE 20

int biggestRect(int mtr[SIZE][SIZE], int row, int col);
int biggestHistogram(int hist[SIZE], int size);

int main(void) {
    // matrisi burdan değiştir
    int matrix[SIZE][SIZE] = {
        {0, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 0, 0}
    };

    // satır ve sütun sayıları
    int row = 4, col = 4;

    printf("%d\n", biggestRect(matrix, row, col));

    return 0;
}

// en büyük dikdörtgeni bulan fonksiyon
int biggestRect(int mtr[SIZE][SIZE], int row, int col) {
    int histogram[SIZE] = {}, i, j, max = 0;

    // satırları teker teker dolaşıcak for
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            // eğer 1 bulursa histogram değerini 1 birim arttır
            if (mtr[i][j] == 1) {
                histogram[j]++;
            }
            // 0 görürse histogramı sıfırla
            else {
                histogram[j] = 0;
            }
        }

        // histogram fonksiyonu ile en büyük alanı bul ve bulunan en büyük değerse max'ı değiştir
        if (biggestHistogram(histogram, col) > max) {
            max = biggestHistogram(histogram, col);
        }
    }

    return max;
}

// bir histogramdaki en büyük dikdörtgeni bulan fonksiyon
int biggestHistogram(int hist[SIZE], int size) {
    int i, j, max = 0, curr;

    // histogram elemanlarını gezmek için for
    for (i = 0; i < size; i++) {
        curr = hist[i];

        // sol taraftaki elemanları gez, eğer hist[i]'den büyük eşitse dörtgenin alanını arttır
        for (j = i - 1; j >= 0 && hist[j] >= hist[i]; j--) {
            curr += hist[i];
        }

        // aynısını sağ tarafa yap
        for (j = i + 1; j < size && hist[j] >= hist[i]; j++) {
            curr += hist[i];
        }

        if (curr > max) {
            max = curr;
        }
    }

    return max;
}
