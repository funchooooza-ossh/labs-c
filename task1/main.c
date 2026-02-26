#include <math.h>
#include <stdlib.h>
#include <stdio.h>



void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// забирает double из ввода 
double getDouble(const char *prompt)
{
    double value;
    int status;

    printf("%s", prompt);
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

// вычисляет дискриминант
double discriminant(double a, double b, double c)
{
    // формула дискриминанта
    return b * b - 4 * a * c;
}

// выводим 2 реальных корня
void solve_two_roots(double D, double a, double b)
{
    double sqrt_D = sqrt(D);
    double x1 = (-b + sqrt_D)/ (2 * a);
    double x2 = (-b - sqrt_D)/ (2 * a);

    printf("Корни: x1 = %.2f, x2 = %.2f\n", x1, x2);
}

// выводим один реальный корень
void solve_single_root(double a, double b)
{
    double x = -b / (2 * a);

    printf("Корень: x = %.2f\n", x);
}

// выводим мнимые корни
void solve_imaginary_roots(double D, double a, double b)
{
    double real = -b / (2 * a);
    double imag = sqrt(-D) / (2 * a);

    printf("Корни квадратного уравнения:\n");
    printf("x1 = %.2f %+.2fi\n", real, imag);
    printf("x2 = %.2f %+.2fi\n", real, -imag);
}

// функция-диспетчер
void solve_quadratic(double D, double a, double b)
{
    if (D > 0)
    {
        printf("Дискриминант=%.2f, уравнение имеет два корня\n", D);
        return solve_two_roots(D, a, b);
    } 
    else if (D == 0)
    {
        printf("Дискриминант=0, уравнение имеет один корень\n");
        return solve_single_root(a, b);
    }
    else
    {
        printf("Дискриминант=%.2f, уравнение имеет мнимые корни\n", D);
        return solve_imaginary_roots(D, a, b);
    }
    
}
/*
точка входа
варианты ввода для теста: 
1,-5,6 (2 корня)
1,-4,4 (1 корень)
1,2,5 (мнимые корни)
*/ 
int main()
{
    double a;
    double b;
    double c;

    a = getDouble("Введите коэффициент a:\n");
    if (a == 0)
    {
        printf("Уравнение не квадратное, a=0\n");
        return 1;
    }
    b = getDouble("Введите коэффициент b:\n");
    c = getDouble("Введите коэффициент c:\n");
    
    double D = discriminant(a, b, c);

    solve_quadratic(D, a, b);

    return 0;
}