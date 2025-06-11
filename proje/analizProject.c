#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define E 2.7182818
#define PI 3.1415926

// Default değerler
#define PRECISION 0.00001
#define ERROR 0.001
#define MAXITERATIONS 100
#define TYPE 1
#define PIECES 2

typedef struct {
    int type;
    char* token;
} TOKEN;

char* getFunc();
int isNum(char ch);
int precedence(char ch);
int isLetter(char ch);
char* infixToRpn(char* str);
float strToNum(char* str);
int findFunc(char* token);
TOKEN* tokenize(char* str, int ind);
float evalRpn(char* rpn, float x);
float** getMatrix(int size);
float* getArr(int size);
void freeMtr(float** mtr, int size);
void printMtr(float** mtr, int size);
int factorial(int n);
float determinant(float** mtr, int size);
float centralNumericDeriv(char* func, float point, float precision);

void bisection(char* rpn, float start, float end, float error, int maxItr);
void regulaFalsi(char* rpn, float start, float end, float error, int maxItr);
void newtonRaphson(char* rpn, float start, float error, int maxItr, int pick, float delta, char* derivRpn);
void inverseMatrix(float** mtr, int size);
void cholesky(float** coefMtr, float* valMtr, int size);
void gaussSeidel(float** coefMtr, float* valMtr, float* startVals, int size, float error);
void numericDeriv(char* rpn, float point, float precision);
float simpson(int type, char* rpn, float bot, float top, int pieces);
float trapezoidal(char* rpn, float bot, float top, int slice);
float gregoryNewton(float* vars, float* vals, float delta, int size, float point);

int main(void) {
    int i, choice = 1, maxItr, pick, size, pieces;
    float start, end, error, delta, point, precision;
    float **coefMtr, *valMtr, *startVals, **mtr, *vars, *vals;
    char *func, *deriv;

    while (choice) {
        printf("Durdur: 0\nBisection: 1\nRegula Falsi: 2\nNewton-Raphson: 3\nTers Matris: 4\nCholesky: 5\nGauss-Seidel: 6\nSayisal Turev: 7\nSimpson Kurali: 8\nTrapez Kurali: 9\nGregory-Newton: 10\n");
        printf("\nTercih: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Program durduruluyor.\n");
                break;
            // Bisection
            case 1:
                func = getFunc();

                printf("Alt sinir degeri: ");
                scanf("%f", &start);
                printf("Ust sinir degeri: ");
                scanf("%f", &end);
                printf("Hata miktari: ");
                scanf("%f", &error);
                printf("Maksimum iterasyon: ");
                scanf("%d", &maxItr);

                bisection(func, start, end, error, maxItr);

                free(func);

                break;
            // Regula-Falsi
            case 2:
                func = getFunc();

                printf("Alt sinir degeri: ");
                scanf("%f", &start);
                printf("Ust sinir degeri: ");
                scanf("%f", &end);
                printf("Hata miktari: ");
                scanf("%f", &error);
                printf("Maksimum iterasyon: ");
                scanf("%d", &maxItr);

                regulaFalsi(func, start, end, error, maxItr);

                free(func);

                break;
            // Newton-Raphson
            case 3:
                func = getFunc();

                printf("Turev yontemi:\nSayisal turev: 1\nTurev fonksiyonu: 2\n");
                scanf("%d", &pick);

                if (pick == 1) {
                    printf("Delta (Hassaslik): ");
                    scanf("%f", &precision);
                }
                else {
                    deriv = getFunc();
                }

                printf("Baslangic degeri: ");
                scanf("%f", &start);
                printf("Hata miktari: ");
                scanf("%f", &error);
                printf("Maksimum iterasyon: ");
                scanf("%d", &maxItr);

                if (pick == 1) {
                    newtonRaphson(func, start, error, maxItr, pick, precision, NULL);
                }
                else {
                    newtonRaphson(func, start, error, maxItr, pick, precision, deriv);
                    free(deriv);
                }

                free(func);

                break;
            // Matrisin Tersi
            case 4:
                printf("Boyut: ");
                scanf("%d", &size);

                if (size <= 0) {
                    printf("\nBoyut yanlis girildi!\n\n");
                }
                else {
                    mtr = getMatrix(size);
    
                    inverseMatrix(mtr, size);
                }

                break;
            // Cholesky
            case 5:
                printf("Katsayi matrisi\n");
                printf("Boyut: ");
                scanf("%d", &size);
                
                if (size <= 1) {
                    printf("\nBoyut yanlis girildi!\n\n");
                }
                else {
                    coefMtr = getMatrix(size);

                    printf("Deger matrisi\n");
                    valMtr = getArr(size);

                    cholesky(coefMtr, valMtr, size);
                }

                break;
            // Gauss-Seidel
            case 6:
                printf("Katsayi matrisi\n");
                printf("Boyut: ");
                scanf("%d", &size);
                
                if (size <= 0) {
                    printf("\nBoyut yanlis girildi!\n\n");
                }
                else {
                    coefMtr = getMatrix(size);
    
                    printf("Deger matrisi\n");
                    valMtr = getArr(size);
    
                    printf("\nBaslangic degerleri\n");
                    startVals = getArr(size);
    
                    printf("\nHata miktari: ");
                    scanf("%f", &error);
    
                    gaussSeidel(coefMtr, valMtr, startVals, size, error);
                }
                
                break;
            // Sayısal Türev
            case 7:
                func = getFunc();

                printf("Nokta: ");
                scanf("%f", &point);
                printf("Delta (Hassaslik): ");
                scanf("%f", &precision);

                numericDeriv(func, point, precision);

                free(func);

                break;
            // Simpson Kuralı
            case 8:
                func = getFunc();

                printf("Kullanilacak yontem:\n1/3: 1\n3/8: 2\n");
                scanf("%d", &pick);
                printf("Alt sinir: ");
                scanf("%f", &start);
                printf("Ust sinir: ");
                scanf("%f", &end);
                printf("Parca sayisi: ");
                scanf("%d", &pieces);

                // 1/3 için parça sayısı çift olmalı
                if (pick == 1 && pieces % 2 != 0) {
                    printf("\nParca sayisi yanlis girildi!\n\n");
                }
                else {
                    printf("\nSonuc: %f\n\n", simpson(pick, func, start, end, pieces));
                }

                free(func);

                break;
            // Trapez Kuralı
            case 9:
                func = getFunc();

                printf("Alt sinir: ");
                scanf("%f", &start);
                printf("Ust sinir: ");
                scanf("%f", &end);
                printf("Parca sayisi: ");
                scanf("%d", &pieces);

                printf("\nSonuc: %f\n\n", trapezoidal(func, start, end, pieces));

                free(func);

                break;
            // Gregory-Newton
            case 10:
                printf("Degisken sayisi: ");
                scanf("%d", &pieces);
                printf("x degerleri arasi fark: ");
                scanf("%f", &delta);

                // Değişken ve fonksiyon değerlerinin tutulduğu diziler
                vars = (float*) malloc(pieces * sizeof(float));
                vals = (float*) malloc(pieces * sizeof(float));

                printf("x0: ");
                scanf("%f", &vars[0]);

                for (i = 1; i < pieces; i++) {
                    vars[i] = vars[i - 1] + delta;
                }

                for (i = 0; i < pieces; i++) {
                    printf("f(x%d): ", i);
                    scanf("%f", &vals[i]);
                }

                printf("Nokta: ");
                scanf("%f", &point);

                if (point > vars[pieces - 1] || point < vars[0]) {
                    printf("\nEnterpolasyon noktasi [x0, x%d] araligi icinde olmali!\n\n", pieces - 1);
                
                    free(vars);
                    free(vals);
                }
                else {
                    printf("\nSonuc: %f\n\n", gregoryNewton(vars, vals, delta, pieces, point));
                }

                break;
            default:
                printf("Yanlis deger girildi!\n\n");
        }
    }

    return 0;
}

// Kullanıcıdan fonksiyon alma
char* getFunc() {
    char string[1024];

    printf("Fonksiyon: ");
    // ' ' (space) yerine '\n' karakteri görene kadar oku
    scanf(" %[^\n]s", string);

    return infixToRpn(string);
}

// Bir char'ın sayı ya da değişken oldup olmadığını döndüren fonksiyon
int isNum(char ch) {
    if (ch - '0' >= 0 && ch - '0' <= 9) {
        return 1;
    }
    if (ch == 'x') {
        return 2;
    }
    if (ch == 'e') {
        return 3;
    }

    return 0;
}

// İşlem önceliğini döndüren fonksiyon
int precedence(char ch) {
    if (ch == '+' || ch == '-') {
        return 1;
    }
    else if (ch == '*' || ch == '/') {
        return 2;
    }
    else if (ch == '^') {
        return 3;
    }
    else if (isLetter(ch)) {
        return 4;
    }
    else {
        return 0;
    }
}

int isLetter(char ch) {
    if (ch >= 'a' && ch <= 'z' && ch != 'x' && ch != 'e') {
        return 1;
    }

    return 0;
}

// Shunting yard algoritması
char* infixToRpn(char* str) {
    int size, i, j = 0, k, top = -1;
    char *output, *stack, ch;

    // String uzunluğu bul
    for (size = 0; str[size] != '\0'; size++);

    // output stringi ve stack'i oluştur
    output = (char*) malloc((2 * size + 1) * sizeof(char));
    stack = (char*) malloc(size * sizeof(char));

    for (i = 0; i < size; i++) {
        ch = str[i];

        if (ch != ' ' && ch != '_') {
            // Eğer sayı ya da değişken okunursa output stringine ekle
            if (isNum(ch)) {
                // Eğer bir önceki okunan eleman da sayıysa çok basamaklı bir sayı girilmiştir, araya boşluk bırakma
                if (i > 0 && isNum(str[i - 1]) == 1) {
                    j--;
                }
                output[j++] = ch;
                output[j++] = ' ';
            }
            // '.' varsa ondalıklı sayıdır, araya boşluk bırakma
            else if (ch == '.') {
                j--;
                output[j++] = ch;
            }
            // '(' okunursa stack'e ekle
            else if (ch == '(') {
                stack[++top] = '(';
            }
            // ')' okunursa '(' bulana kadar stack'ten çıkarıp outputa ekle
            else if (ch == ')') {
                while (top >= 0 && stack[top] != '(') {
                    // Trig ya da log görürse boşluk bırakmadan ekle
                    if (isLetter(stack[top])) {
                        while (top >= 0 && isLetter(stack[top])) {
                            output[j++] = stack[top--];
                        }
            
                        output[j++] = ' ';
                    }
                    else {
                        output[j++] = stack[top--];
                
                        output[j++] = ' ';
                    }
                }
    
                top--;
            }
            // Operatör okunursa
            else {
                // İşlem önceliği daha düşük bir operatör geldiyse alttakileri outputa ekle
                while (top >= 0 && (precedence(ch) <= precedence(stack[top]))) {
                    // Trig ya da log görürse boşluk bırakmadan ekle
                    if (isLetter(stack[top])) {
                        while (top >= 0 && isLetter(stack[top])) {
                            output[j++] = stack[top--];
                        }
            
                        output[j++] = ' ';
                    }
                    else {
                        output[j++] = stack[top--];
                
                        output[j++] = ' ';
                    }
                }

                // Trig ya da log görürse hepsini birden stack'e ekle
                if (isLetter(ch)) {
                    for (k = i; k < size && isLetter(str[k]); k++);
                    for (k -= 1; k >= i; k--) {
                        stack[++top] = str[k];
                        str[k] = ' ';
                    }
                }
                else {
                    stack[++top] = ch;
                }
            }
        }
    }

    // Stack'te kalan elemanları outputa ekle
    while (top >= 0) {
        // Trig ya da log görürse boşluk bırakmadan ekle
        if (isLetter(stack[top])) {
            while (top >= 0 && isLetter(stack[top])) {
                output[j++] = stack[top--];
            }

            output[j++] = ' ';
        }
        else {
            output[j++] = stack[top--];
    
            output[j++] = ' ';
        }
    }

    output[j] = '\0';

    free(stack);

    return output;
}

// Stringi floata çeviren fonksiyon
float strToNum(char* str) {
    int i, onDecimal = 0, pow = 10;
    float num = 0;
    
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            onDecimal = 1;
        }
        else {
            if (onDecimal) {
                num += (float) (str[i] - '0') / pow;
                pow *= 10;
            }
            else {
                num *= 10;
                num += str[i] - '0';
            }
        }
    }

    return num;
}

// Stringin hangi fonksiyon olduğunu döndüren fonksiyon
int findFunc(char* token) {
    if (strcmp(token, "sin") == 0) {
        return 1;
    }
    else if (strcmp(token, "cos") == 0) {
        return 2;
    }
    else if (strcmp(token, "tan") == 0) {
        return 3;
    }
    else if (strcmp(token, "cot") == 0) {
        return 4;
    }
    else if (strcmp(token, "arcsin") == 0 || strcmp(token, "asin") == 0) {
        return 5;
    }
    else if (strcmp(token, "arccos") == 0 || strcmp(token, "acos") == 0) {
        return 6;
    }
    else if (strcmp(token, "arctan") == 0 || strcmp(token, "atan") == 0) {
        return 7;
    }
    else if (strcmp(token, "atan") == 0 || strcmp(token, "acot") == 0) {
        return 8;
    }
    else if (strcmp(token, "ln") == 0) {
        return 9;
    }
    else if (strcmp(token, "log") == 0) {
        return 10;
    }
    else if (strcmp(token, "sqrt") == 0) {
        return 11;
    }

    return 0;
}

// Stringi tokenlere bölen fonksiyon
TOKEN* tokenize(char* str, int ind) {
    TOKEN* token = (TOKEN*) malloc(sizeof(TOKEN));
    char* tokenStr = (char*) malloc(16 * sizeof(char));
    int i = 0;

    // Parametre olarak verilen indisten başlayıp boşluk görene kadar oku
    while (str[ind + i] != '\0' && str[ind + i] != ' ') {
        tokenStr[i] = str[ind + i];
        i++;
    }

    tokenStr[i] = '\0';
    token->token = tokenStr;
    
    // Tokenin türünü belirleme
    if (isNum(tokenStr[0])) {
        token->type = isNum(tokenStr[0]);
    }
    // Pi sabiti
    else if (strcmp("pi", tokenStr) == 0) {
        token->type = 4;
    }
    else {
        // Temel operatörler
        switch (tokenStr[0]) {
            case '+':
                token->type = 5;
                break;
            case '-':
                token->type = 6;
                break;
            case '*':
                token->type = 7;
                break;
            case '/':
                token->type = 8;
                break;
            case '^':
                token->type = 9;
                break;
        }

        // Fonksiyonlar
        if (findFunc(tokenStr)) {
            token->type = findFunc(tokenStr) + 9;
        }
    }

    return token;
}

// Postfix hesap makinesi
float evalRpn(char* rpn, float x) {
    int top = -1, size, index = 0;
    float *stack, temp;
    TOKEN* token;

    for (size = 0; rpn[size] != '\0'; size++);
    
    stack = (float*) malloc(size * sizeof(float));

    while (index < size) {
        // Stringi tokenlere böl
        token = tokenize(rpn, index);

        switch (token->type) {
            case 1:
                stack[++top] = strToNum(token->token);
                break;
            case 2:
                stack[++top] = x;
                break;
            case 3:
                stack[++top] = E;
                break;
            case 4:
                stack[++top] = PI;
                break;
            case 5:
                temp = stack[top] + stack[top - 1];
                top -= 2;
                stack[++top] = temp;
                break;
            case 6:
                temp = stack[top - 1] - stack[top];
                top -= 2;
                stack[++top] = temp;
                break;
            case 7:
                temp = stack[top] * stack[top - 1];
                top -= 2;
                stack[++top] = temp;
                break;
            case 8:
                temp = stack[top - 1] / stack[top];
                top -= 2;
                stack[++top] = temp;
                break;
            case 9:
                temp = pow(stack[top - 1], stack[top]);
                top -= 2;
                stack[++top] = temp;
                break;
            case 10:
                temp = sin(stack[top--]);
                stack[++top] = temp;
                break;
            case 11:
                temp = cos(stack[top--]);
                stack[++top] = temp;
                break;
            case 12:
                temp = tan(stack[top--]);
                stack[++top] = temp;
                break;
            case 13:
                temp = 1 / tan(stack[top--]);
                stack[++top] = temp;
                break;
            case 14:
                temp = asin(stack[top--]);
                stack[++top] = temp;
                break;
            case 15:
                temp = acos(stack[top--]);
                stack[++top] = temp;
                break;
            case 16:
                temp = atan(stack[top--]);
                stack[++top] = temp;
                break;
            case 17:
                temp = 1 / atan(stack[top--]);
                stack[++top] = temp;
                break;
            case 18:
                temp = log(stack[top--]);
                stack[++top] = temp;
                break;
            case 19:
                temp = log(stack[top]) / log(stack[top - 1]);
                top -= 2;
                stack[++top] = temp;
                break;
            case 20:
                temp = sqrt(stack[top--]);
                stack[++top] = temp;
                break;
        }
    
        index += strlen(token->token) + 1;
        free(token->token);
        free(token);
    }

    temp = stack[top];
    free(stack);

    return temp;
}

// Matris almak için fonksiyon
float** getMatrix(int size) {
    int i, j;
    float** mtr;

    // Dinamik olarak yer açma
    mtr = (float**) malloc(size * sizeof(float*));
    for (i = 0; i < size; i++) {
        mtr[i] = (float*) malloc(size * sizeof(float));
    }

    // Matris değerlerini alma
    printf("\n");
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("[%d][%d]: ", i, j);
            scanf("%f", &mtr[i][j]);
        }
    }

    // Matrisi yazdırma
    printf("\nMatris: [\n    ");
    printMtr(mtr, size);

    return mtr;
}

// Dizi almak için fonksiyon
float* getArr(int size) {
    int i;
    float* arr;

    // Yer açma
    arr = (float*) malloc(size * sizeof(float));

    // Değerleri alma
    for (i = 0; i < size; i++) {
        printf("[%d]: ", i);
        scanf("%f", &arr[i]);
    }

    // Diziyi yazdırma
    printf("\nMatris: [\n    ");
    for (i = 0; i < size; i++) {
        printf("%f\n    ", arr[i]);
    }
    printf("\r]\n");

    return arr;
}

// Bisection yöntemi
void bisection(char* func, float start, float end, float error, int maxItr) {
    float mid, bot = start, top = end, prev = top;
    int flag = 1, iterations = 1;

    // Yanlış değer girildiyse default değerleri kullan
    if (error <= 0) {
        error = ERROR;
    }
    if (maxItr <= 0) {
        maxItr = MAXITERATIONS;
    }

    while (flag && iterations <= maxItr) {
        mid = (bot + top) / 2;

        // İterasyonları yazdırma
        printf("\n");
        printf("iterasyon : %d\n", iterations);
        printf("alt       : %f\n", bot);
        printf("ust       : %f\n", top);
        printf("orta      : %f\n", mid);
        printf("f(alt)    : %f\n", evalRpn(func, bot));
        printf("f(ust)    : %f\n", evalRpn(func, top));
        printf("f(orta)   : %f\n", evalRpn(func, mid));

        // Sınırları kaydırma
        if (evalRpn(func, bot) * evalRpn(func, mid) < 0) {
            top = mid;
        }
        else if (evalRpn(func, mid) * evalRpn(func, top) < 0) {
            bot = mid;
        }
        else if (evalRpn(func, mid) == 0) {
            flag = 0;
        }
        else if (evalRpn(func, bot) == 0) {
            flag = 0;
            mid = bot;
        }
        else if (evalRpn(func, top) == 0) {
            flag = 0;
            mid = top;
        }

        if (fabs(mid - prev) <= error) {
            flag = 0;
        }

        prev = mid;
        iterations++;
    }

    printf("\nSonuc: %f\n\n", mid);
}

// Regula Falsi yöntemi
void regulaFalsi(char* func, float start, float end, float error, int maxItr) {
    float mid, bot = start, top = end, prev = top;
    int flag = 1, iterations = 1;

    // Yanlış değer girildiyse default değerleri kullan
    if (error <= 0) {
        error = ERROR;
    }
    if (maxItr <= 0) {
        maxItr = MAXITERATIONS;
    }

    while (flag && iterations <= maxItr) {
        mid = (top * evalRpn(func, bot) - bot * evalRpn(func, top)) / (evalRpn(func, bot) - evalRpn(func, top));

        // İterasyonları yazdırma
        printf("\n");
        printf("iterasyon : %d\n", iterations);
        printf("alt       : %f\n", bot);
        printf("ust       : %f\n", top);
        printf("nokta     : %f\n", mid);
        printf("f(alt)    : %f\n", evalRpn(func, bot));
        printf("f(ust)    : %f\n", evalRpn(func, top));
        printf("f(nokta)  : %f\n", evalRpn(func, mid));

        // Sınırları kaydırma
        if (evalRpn(func, bot) * evalRpn(func, mid) < 0) {
            top = mid;
        }
        else if (evalRpn(func, mid) * evalRpn(func, top) < 0) {
            bot = mid;
        }
        else if (evalRpn(func, mid) == 0) {
            flag = 0;
        }
        else if (evalRpn(func, bot) == 0) {
            flag = 0;
            mid = bot;
        }
        else if (evalRpn(func, top) == 0) {
            flag = 0;
            mid = top;
        }

        if (fabs(mid - prev) <= error) {
            flag = 0;
        }

        prev = mid;
        iterations++;
    }

    printf("\nSonuc: %f\n\n", mid);
}

// Newton-Raphson yöntemi
void newtonRaphson(char* func, float start, float error, int maxItr, int pick, float delta, char* derivative) {
    int flag = 1, iterations = 1;
    float point, prev = start;

    // Yanlış değer girildiyse default değerleri kullan
    if (error <= 0) {
        error = ERROR;
    }
    if (maxItr <= 0) {
        maxItr = MAXITERATIONS;
    }

    while (flag && iterations < maxItr) {
        if (pick == 1) {
            point = prev - evalRpn(func, prev) / centralNumericDeriv(func, prev, delta);
        }
        else {
            point = prev - evalRpn(func, prev) / evalRpn(derivative, prev);
        }

        // İterasyonları yazdırma
        printf("\n");
        printf("iterasyon : %d\n", iterations);
        printf("xn        : %f\n", prev);
        printf("xn+1      : %f\n", point);
        printf("f(xn)     : %f\n", evalRpn(func, prev));
        if (pick == 1) {
            printf("f'(xn)    : %f\n", centralNumericDeriv(func, prev, delta));
        }
        else {
            printf("f'(xn)    : %f\n", evalRpn(derivative, prev));
        }

        if (fabs(point - prev) <= error) {
            flag = 0;
        }

        prev = point;
        iterations++;
    }

    printf("\nSonuc: %f\n\n", point);
}

// Gauss-Jordan Eliminasyonu ile matrisin tersi
void inverseMatrix(float** mtr, int size) {
    int i, j, k, flag = 1;
    float key, mult, **unit, tmp;

    // Determinant sıfırsa fonksiyonu bitir
    if (!determinant(mtr, size)) {
        printf("Matrisin tersi bulunamadi!\n\n");

        freeMtr(mtr, size);

        return;
    }

    // Birim matris oluşturma
    unit = (float**) calloc(size, sizeof(float*));
    for (i = 0; i < size; i++) {
        unit[i] = (float*) calloc(size, sizeof(float));
    }

    for (i = 0; i < size; i++) {
        unit[i][i] = 1;
    }

    // Üst üçgensel yapma
    for (i = 0; i < size; i++) {
        key = mtr[i][i];

        // Eğer ilk eleman 0 ise başka bir satırla değiştirme
        if (!key) {
            flag = 0;
            for (j = i + 1; j < size; j++) {
                if (mtr[j][i] && !flag) {
                    key = mtr[j][i];
                    flag = 1;

                    for (k = 0; k < size; k++) {
                        tmp = mtr[i][k];
                        mtr[i][k] = mtr[j][k];
                        mtr[j][k] = tmp;
                        
                        tmp = unit[i][k];
                        unit[i][k] = unit[j][k];
                        unit[j][k] = tmp;
                    }
                }
            }
        }

        // Satırı ilk elemana bölme
        for (j = 0; j < size; j++) {
            mtr[i][j] /= key;
            unit[i][j] /= key;
        }

        // Aşağıdaki satırlardan çıkar
        for (k = i + 1; k < size; k++) {
            mult = mtr[k][i];
            for (j = 0; j < size; j++) {
                mtr[k][j] -= mult * mtr[i][j];
                unit[k][j] -= mult * unit[i][j];
            }
        }
    }
    
    // Birim matrise çevirme
    for (i = size - 1; i >= 0; i--) {
        for (j = i - 1; j >= 0; j--) {
            mult = mtr[j][i];
            for (k = 0; k < size; k++) {
                mtr[j][k] -= mult * mtr[i][k];
                unit[j][k] -= mult * unit[i][k];
            }
        }
    }

    printf("Ters matris: [\n    ");
    printMtr(unit, size);

    freeMtr(mtr, size);
    freeMtr(unit, size);
}

// Cholesky (ALU) yöntemi
void cholesky(float** coefMtr, float* valMtr, int size) {
    int i, j, k;
    float **L, **U, *Y, *X;

    // L, U, Y ve X matrisleri için yer açma
    L = (float**) malloc(size * sizeof(float*));
    for (i = 0; i < size; i++) {
        L[i] = (float*) malloc(size * sizeof(float)); 
    }

    U = (float**) malloc(size * sizeof(float*));
    for (i = 0; i < size; i++) {
        U[i] = (float*) malloc(size * sizeof(float)); 
    }

    Y = (float*) malloc(size * sizeof(float));
    X = (float*) malloc(size * sizeof(float));

    // L ve U matrislerini doldurma
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (j <= i) {
                U[j][i] = coefMtr[j][i];

                for (k = 0; k <= j - 1; k++) {
                    U[j][i] -= L[j][k] * U[k][i];
                }

                if (i == j) {
                    L[j][i] = 1;
                }
                else {
                    L[j][i] = 0;
                }
            }
            else {
                L[j][i] = coefMtr[j][i];

                for (k = 0; k <= i - 1; k++) {
                    L[j][i] -= L[j][k] * U[k][i];
                }
                
                L[j][i] /= U[i][i];
                U[j][i] = 0;
            }
        }
    }

    printf("\nL Matrisi: [\n    ");
    printMtr(L, size);

    printf("U Matrisi: [\n    ");
    printMtr(U, size);

    // Y matrisini bulma (LY = B)
    for (i = 0; i < size; i++) {
        Y[i] = valMtr[i];
        
        for (j = 0; j < i; j++) {
            Y[i] -= L[i][j] * Y[j];
        }
    }

    printf("Y Matrisi: [\n    ");
    for (i = 0; i < size; i++) {
        printf("%f\n    ", Y[i]);
    }
    printf("\r]\n\n");

    // Değer matrisini bulma (UX = Y)
    for (i = size - 1; i >= 0; i--) {
        X[i] = Y[i];

        for (j = i + 1; j < size; j++) {
            X[i] -= U[i][j] * X[j];
        }

        X[i] /= U[i][i];
    }

    printf("X Matrisi: [\n    ");
    for (i = 0; i < size; i++) {
        printf("%f\n    ", X[i]);
    }
    printf("\r]\n\n");

    // Kullanılan yeri geri salma
    freeMtr(coefMtr, size);
    free(valMtr);
    freeMtr(L, size);
    freeMtr(U, size);
    free(X);
    free(Y);
}

// Gauss-Seidel yöntemi
void gaussSeidel(float** coefMtr, float* valMtr, float* startVals, int size, float error) {
    int i, j, iterations = 0, flag = 1, index;
    float *ind, max = 0, tmp, *prevVals, key = 0;

    // Yanlış değer girildiyse default değerleri kullan
    if (error <= 0) {
        error = ERROR;
    }
    
    // Önceki iterasyon değerlerini tutan dizi
    prevVals = (float*) malloc(size * sizeof(float));

    // Her sütundaki mutlakça en büyük elemanını bulup satırları değiştirme
    for (i = 0; i < size; i++) {
        max = 0;
        for (j = 0; j < size; j++) {
            if (fabs(coefMtr[j][i]) >= max) {
                max = coefMtr[j][i];
                ind = &coefMtr[j][i];
                index = j;
            }
        }

        for (j = 0; j < size; j++) {
            tmp = coefMtr[i][j];
            coefMtr[i][j] = *(ind + j - i);
            *(ind + j - i) = tmp;

            tmp = valMtr[i];
            valMtr[i] = valMtr[index];
            valMtr[index] = tmp;
        }
    }

    printf("\nKosegen Elemanlari Carpimi Max Olan Matris: [\n    ");
    printMtr(coefMtr, size);

    // Değişkenlerin bulunduğu loop
    do {
        for (i = 0; i < size; i++) {
            key = valMtr[i];
            prevVals[i] = startVals[i];
            
            for (j = 0; j < size; j++) {
                if (i != j) {
                    key -= coefMtr[i][j] * startVals[j];
                }
            }
            key /= coefMtr[i][i];
            startVals[i] = key;

            for (j = 0; j < size; j++) {
                flag = 0;
                if (fabs(prevVals[i] - startVals[i]) > error) {
                    flag = 1;
                }
            }
        }

        iterations++;

        // Yazdırma
        printf("iterasyon : %d\n", iterations);
        for (i = 0; i < size; i++) {
            printf("x%d        : %f\n", i, startVals[i]);
        }
        printf("\n");
    } while (iterations < MAXITERATIONS && flag);

    if (iterations >= MAXITERATIONS) {
        printf("Iterasyon limitine ulasildi!\n");
    }

    printf("Degisken Matrisi: [\n    ");
    for (i = 0; i < size; i++) {
        printf("%f\n    ", startVals[i]);
    }
    printf("\r]\n\n");

    freeMtr(coefMtr, size);
    free(valMtr);
    free(startVals);
    free(prevVals);
}

// Sayısal türev
void numericDeriv(char* func, float point, float precision) {
    float back, forw, center;

    // Yanlış değer girildiyse default değerleri kullan
    if (precision <= 0) {
        precision = PRECISION;
    }

    back = (evalRpn(func, point) - evalRpn(func, point - precision)) / precision;
    forw = (evalRpn(func, point + precision) - evalRpn(func, point)) / precision;
    center = (evalRpn(func, point + precision) - evalRpn(func, point - precision)) / (2 * precision);

    printf("\nGeri fark: %f\nIleri fark: %f\nMerkezi fark: %f\n\n", back, forw, center);
}

// Simpson kuralı
float simpson(int type, char* func, float bot, float top, int pieces) {
    int i;
    float delta, area = 0;

    // Yanlış değer girildiyse default değerleri kullan
    if (pieces <= 0) {
        pieces = PIECES;
    }
    if (type != 1 && type != 2) {
        type = TYPE;
    }

    // 1/3
    if (type == 1) {
        delta = (top - bot) / pieces;

        area += evalRpn(func, bot) + evalRpn(func, top);

        // Tek sayı indisli parçalar
        for (i = 0; i < pieces / 2; i++) {
            area +=  4 * evalRpn(func, bot + delta * (2 * i + 1));
        }

        // Çift sayı indisli parçalar
        for (i = 1; i < pieces / 2; i++) {
            area += 2 * evalRpn(func, bot + delta * (2 * i));
        }

        area = area * delta / 3;
    }
    // 3/8
    else {
        if (pieces == 1) {
            delta = (top - bot) / 3;

            area += (top - bot) * (evalRpn(func, bot) + evalRpn(func, top) + 3 * evalRpn(func, bot + delta) + 3 * evalRpn(func, bot + 2 * delta)) / 8;
        }
        // Birden fazla parça girilmişse integral parça parça özyinelemeli olarak yapılıyor
        else {
            delta = (top - bot) / pieces;
            
            for (i = 0; i < pieces; i++) {
                area += simpson(2, func, bot + delta * i, bot + delta * (i + 1), 1);
            }
        }
    }

    return area;
}

// Trapez kuralı
float trapezoidal(char* func, float bot, float top, int slice) {
    float width = (top - bot) / slice, area = 0;
    int i;

    // Yanlış değer girildiyse default değerleri kullan
    if (slice <= 0) {
        slice = PIECES;
    }

    for (i = 0; i < slice; i++) {
        area += width / 2 * (evalRpn(func, bot + i * width) + evalRpn(func, bot + (i + 1) * width));
    }

    return area;
}

// Gregory-Newton interpolasyonu
float gregoryNewton(float* vars, float* vals, float delta, int size, float point) {
    float** diffs;
    float num = 0, mult;
    int i, j, k, flag = 1;

    // İleri farkların tutulduğu matris
    diffs = (float**) malloc(size * sizeof(float*));
    for (i = 0; i < size; i++) {
        diffs[i] = (float*) malloc((size + 1) * sizeof(float));
    }

    // Fark matrisinin ilk sütununu fonksiyon değerlerine eşitleme
    for (i = 0; i < size; i++) {
        diffs[i][0] = vals[i];
    }

    // İleri farkları bulma
    i = 1;
    while (flag) {
        for (j = 0; j < size - i; j++) {
            diffs[j][i] = diffs[j + 1][i - 1] - diffs[j][i - 1];
        }

        flag = 0;
        for (j = 1; j < size - i; j++) {
            if (diffs[j][i] != diffs[j - 1][i]) {
                flag = 1;
            }
        }

        i++;
    }

    // Enterpolasyon fonksiyonunu yazdırma
    printf("\nEnterpolasyon Polinomu:\n%f + ", diffs[0][0]);
    for (j = 1; j < i; j++) {
        for (k = 0; k < j; k++) {
            printf("(x - %f)", vars[k]);
        }
        printf(" * %f / (%d * %f) + ", diffs[0][j], factorial(j), pow(delta, j));
    }
    printf("\b\b \n");

    // Enterpolasyonu gerçekleştirme
    num += vals[0];

    for (j = 1; j <= i; j++) {
        mult = 1;
        for (k = 0; k < j; k++) {
            mult *= point - vars[k];
        }
        
        num += mult * diffs[0][j] / factorial(j) / pow(delta, j);
    }

    for (i = 0; i < size; i++) {
        free(diffs[i]);
    }
    free(diffs);
    free(vars);
    free(vals);

    return num;
}

// Matris için bellekte açılan yerin geri salınması için fonksiyon
void freeMtr(float** mtr, int size) {
    int i;

    for (i = 0; i < size; i++) {
        free(mtr[i]);
    }
    free(mtr);
}

// Kare matris yazdırmak için fonksiyon
void printMtr(float** mtr, int size) {
    int i, j;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%f    ", mtr[i][j]);
        }
        printf("\n    ");
    }
    printf("\r]\n\n");
}

// Faktöriyel fonksiyonu
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

// Determinantı Laplace açılımı ile bulan fonksiyon
float determinant(float** mtr, int size) {
    float **minor;
    int i, j, k;
    float det = 0, tempDet;

    if (size == 1) {
        return mtr[0][0];
    }

    // Minör matrisi için yer açma
    minor = (float**) malloc((size - 1) * sizeof(float*));
    for (i = 0; i < size - 1; i++) {
        minor[i] = (float*) malloc((size - 1) * sizeof(float));
    }

    // İlk satır için Laplace açılımı
    for (i = 0; i < size; i++) {
        // Minör matrisi oluşturma, önce sol sonra sağ taraf
        for (j = 1; j < size; j++) {
            for (k = 0; k < i; k++) {
                minor[j - 1][k] = mtr[j][k];
            }
            for (k = i + 1; k < size; k++) {
                minor[j - 1][k - 1] = mtr[j][k];
            }
        }

        // Minörün determinantını bulma
        tempDet = determinant(minor, size - 1);
        
        // Determinantı hesaplama
        det += (i & 1 ? -1 : 1) * (mtr[0][i] * tempDet);
    }
    
    freeMtr(minor, size - 1);

    return det;
}

// Merkezi fark sayısal türev (Newton-Raphson için)
float centralNumericDeriv(char* func, float point, float precision) {
    // Yanlış değer girildiyse default değerleri kullan
    if (precision <= 0) {
        precision = PRECISION;
    }

    return (evalRpn(func, point + precision) - evalRpn(func, point - precision)) / (2 * precision);
}
