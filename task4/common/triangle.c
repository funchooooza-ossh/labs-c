#include "math.h"
#include "triangle.h"

/*
проверяет валидность треугольника по его сторонам
возвращает 0, если все окей
1, если треугольник некорректный
*/
int isValidTriangle(double a, double b, double c)
{
    if (a + b > c && a + c > b && b + c > a)
    {
        return 0;
    }
    return 1;
}
// вычисляет периметр треугольника
double trianlge_perimeter(double a, double b, double c)
{
    return a + b + c;
}

// вычисляет площадь треугольника
double triangle_area(double P, double a, double b, double c)
{
    double half_p = P/2;

    return sqrt(half_p * (half_p - a) * (half_p - b) * (half_p - c));
}