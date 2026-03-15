#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define COUNT 4

#define inputFilePath "input.txt"
#define outputFilePath "output/output.txt"

typedef struct {
    char name[MAX_NAME];
    char surname[MAX_NAME];
    int birth_year;
} Human;

// Сортирует массив людей по году рождения (пузырьковая сортировка)
void sort_by_year(Human arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].birth_year > arr[j + 1].birth_year) {
                // Меняем местами
                Human temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    FILE *input = fopen(inputFilePath, "r");
    if (!input) {
        fprintf(stderr, "Ошибка открытия %s\n", inputFilePath);
        return 1;
    }
    
    // Массив из 4 элементов типа Human
    Human humans[COUNT];
    int count = 0;
    
    // Читаем данные из файла
    while (count < COUNT && 
           fscanf(input, "%s %s %d", 
                  humans[count].surname, 
                  humans[count].name, 
                  &humans[count].birth_year) == 3) {
        count++;
    }
    fclose(input);
    
    // Выводим исходный массив
    printf("Исходный массив:\n");
    for (int i = 0; i < count; i++) {
        printf("%s %s %d\n", 
               humans[i].surname, 
               humans[i].name, 
               humans[i].birth_year);
    }
    
    // Сортируем по году рождения
    sort_by_year(humans, count);
    
    // Выводим отсортированный массив в консоль
    printf("\nОтсортированный по году рождения:\n");
    for (int i = 0; i < count; i++) {
        printf("%s %s %d\n", 
               humans[i].surname, 
               humans[i].name, 
               humans[i].birth_year);
    }
    
    // Записываем результат в файл
    FILE *output = fopen(outputFilePath, "w");
    if (!output) {
        fprintf(stderr, "Ошибка открытия %s\n", outputFilePath);
        return 1;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(output, "%s %s %d\n", 
                humans[i].surname, 
                humans[i].name, 
                humans[i].birth_year);
    }
    fclose(output);

    printf("\nРезультат записан в %s\n", outputFilePath);
    return 0;
}