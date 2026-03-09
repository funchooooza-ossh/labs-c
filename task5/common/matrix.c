#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

double** matrix_sum(const double** a, const double** b, int n) {
    // выделяем память под итоговую матрицу
    double** result = (double**)malloc(n * sizeof(double*));
    if (!result) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    
    for (int i = 0; i < n; i++) {
        result[i] = (double*)malloc(n * sizeof(double));
        if (!result[i]) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            exit(1);
        }
        
        for (int j = 0; j < n; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    
    return result;
}

double** matrix_sub(const double** a, const double** b, int n) {
    double** result = (double**)malloc(n * sizeof(double*));
    if (!result) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    
    for (int i = 0; i < n; i++) {
        result[i] = (double*)malloc(n * sizeof(double));
        if (!result[i]) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            exit(1);
        }
        
        for (int j = 0; j < n; j++) {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
    
    return result;
}

double** matrix_mul(const double** a, const double** b, int n) {
    double** result = (double**)malloc(n * sizeof(double*));
    if (!result) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    
    for (int i = 0; i < n; i++) {
        result[i] = (double*)malloc(n * sizeof(double));
        if (!result[i]) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            exit(1);
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] = a[i][k] * b[k][j];
            }
        }
    }
    
    return result;
}