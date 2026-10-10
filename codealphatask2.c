#include <stdio.h>

#define N 2

void readMatrix(int a[N][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &a[i][j]);
        }
    }
}

void displayMatrix(int a[N][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void addMatrix(int a[N][N], int b[N][N],
               int result[N][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiplyMatrix(int a[N][N], int b[N][N],
                    int result[N][N]) {
    int i, j, k;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            result[i][j] = 0;

            for (k = 0; k < N; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transposeMatrix(int a[N][N], int result[N][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            result[j][i] = a[i][j];
        }
    }
}

int main() {
    int a[N][N], b[N][N];
    int result[N][N];

    printf("Enter 4 elements of Matrix A:\n");
    readMatrix(a);

    printf("Enter 4 elements of Matrix B:\n");
    readMatrix(b);

    printf("\nMatrix A:\n");
    displayMatrix(a);

    printf("\nMatrix B:\n");
    displayMatrix(b);

    addMatrix(a, b, result);
    printf("\nMatrix Addition:\n");
    displayMatrix(result);

    multiplyMatrix(a, b, result);
    printf("\nMatrix Multiplication:\n");
    displayMatrix(result);

    transposeMatrix(a, result);
    printf("\nTranspose of Matrix A:\n");
    displayMatrix(result);

    return 0;
}