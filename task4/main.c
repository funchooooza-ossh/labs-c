#include "triangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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

int main()
{
    double a = getDouble("Введите длину стороны(a)\n");
    double b = getDouble("Введите длину стороны(b)\n");
    double c = getDouble("Введите длину стороны(c)\n");

    int valid = isValidTriangle(a,b,c);
    if (valid == 1)
    {
        printf("Треугольник с данными сторонами %.2f %.2f %.2f не может существовать\n", a, b, c);
        return 1;
    }
    
    double P = trianlge_perimeter(a,b,c);
    double S = triangle_area(P,a,b,c);

    printf("P=%.2f\n", P);
    printf("S=%.2f\n", S);


    return 0;
}