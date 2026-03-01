#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>



void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

// забирает int из ввода
int getInt()
{
    long long buff;
    int status;
    
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

// лимит из задания для первой матрицы
#define LIMIT 3
// лимит из задания для второй матрицы
#define LIMIT2 2 

/*
точка входа
*/
int main()
{
    double matrix3[LIMIT][LIMIT];
    int matrix2[LIMIT2][LIMIT2];

    // LINK наполнение первой матрицы
    for (int i = 0; i < LIMIT; i++)
    {
        for (int j = 0; j < LIMIT; j++)
        {
            printf("Введите элемент[%d][%d]:\n", i+1, j+1);
            matrix3[i][j] = getDouble();
        }
    }

    double main_sum = 0;
    double sub_sum = 0;

    // LINK считаем суммы за один проход
    for (int i = 0; i < LIMIT; i++)
    {
        main_sum += matrix3[i][i];
        sub_sum += matrix3[i][LIMIT-i-1];
    }
    printf("Сумма элементов главной диагонали: %.2f\n", main_sum);
    printf("Сумма элементов побочной диагонали: %.2f\n", sub_sum);

    // LINK наполнение второй матрицы
    for (int i = 0; i < LIMIT2; i++)
    {
        for (int j = 0; j < LIMIT2; j++)
        {
            printf("Введите элемент[%d][%d]:\n", i+1, j+1);
            matrix2[i][j] = getInt();
        }
    }

    // LINK поскольку с итоговой матрицей ничего делать не нужно - просто выведем ее
    printf("Итоговая матрица в квадрате:\n");
    for (int i = 0; i < LIMIT2; i++) // строки
    {
        for (int j = 0; j < LIMIT2; j++) // столбцы
        {
            int sum = 0;
            for (int k = 0; k < LIMIT2; k++) // суммирование
            {
                sum += matrix2[i][k] * matrix2[k][j];
            }
            printf("%6d ", sum);
        }
        printf("\n");
    }

}