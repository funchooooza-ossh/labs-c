#include "matrix.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// забирает int из ввода
int getInt(const char *prompt)
{
    long long buff;
    int status;

    printf("%s", prompt);
    
    while(1)
    {
        status = scanf("%lld", &buff);

        if (status == EOF)
        {
            exit(1);
        }
        if (buff >= INT_MIN && buff <= INT_MAX)
        {
            return (int)buff;
        }
        else
        {
            printf("Число вне допустимого диапазона (%d ... %d)\n", INT_MIN, INT_MAX);
        }
        clearBuffer();
    }
}

// забирает double из ввода 
double getDouble()
{
    double value;
    int status;

    while(1)
    {
        status = scanf("%lf", &value);

        if (status == EOF)
        {
            exit(1);
        }
        if (status == 1)
        {
            if (isfinite(value))
            {
                return value;
            }
            else
            {
                printf("Число слишком велико для обработки");
            }
        }
        clearBuffer();
    }
}

int main()
{
    int n = getInt("Введите желаемую размерность матриц:\n");
    //LINK выделяем память
    double** matrix1 = (double**)malloc(n * sizeof(double*));
    double** matrix2 = (double**)malloc(n * sizeof(double*));


    printf("Введите элементы матрицы1:\n");
    for (int i = 0; i < n; i++)
    {
        // LINK при заполнении матрицы выделяем память под каждую строку
        matrix1[i] = (double*)malloc(n * sizeof(double));
        if (!matrix1[i])
        {
            fprintf(stderr, "Ошибка выделения памяти\n");
            exit(1);
        }
        
        for (int j = 0; j < n; j++)
        {
            printf("Введите элемент[%d][%d]:\n", i+1, j+1);
            matrix1[i][j] = getDouble();
        }
    }
    printf("Введите элементы матрицы2:\n");
    for (int i = 0; i < n; i++)
    {
        // LINK при заполнении матрицы выделяем память под каждую строку
        matrix2[i] = (double*)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++)
        {
            printf("Введите элемент[%d][%d]:\n", i+1, j+1);
            matrix2[i][j] = getDouble();
        }
    }

    char op;

    printf("Введите операцию (+, -, *):\n");
    // обязательно пробел, чтобы не считать \n после ввода значений матрицы
    scanf(" %c", &op);
    
    double** result = NULL;
    
    switch (op) {
        case '+':
            result = matrix_sum((const double**)matrix1, (const double**)matrix2, n);
            printf("Сумма матриц:\n");
            break;
        case '-':
            result = matrix_sub((const double**)matrix1, (const double**)matrix2, n);
            printf("Разность матриц (A - B):\n");
            break;
        case '*':
            result = matrix_mul((const double**)matrix1, (const double**)matrix2, n);
            printf("Произведение матриц:\n");
            break;
        default:
            printf("Неверная операция\n");
            return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", result[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < n; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
        free(result[i]);
    }

    free(matrix1);
    free(matrix2);
    free(result);
    
    return 0;
}
    