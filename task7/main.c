#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_LINE 256


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
    
    // LINK Сначала считаем количество строк в файле
    int count = 0;
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (ch == '\n') count++;
    }
    rewind(input); // возвращаемся в начало файла
    
    if (count == 0) {
        fprintf(stderr, "Файл пуст\n");
        fclose(input);
        return 1;
    }
    
    // LINK Выделяем память под массив
    Human *humans = (Human*)malloc(count * sizeof(Human));
    if (!humans) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        fclose(input);
        return 1;
    }
    
    // LINK Читаем данные из файла
    int actual_count = 0;
    char line[MAX_LINE];
    
    while (fgets(line, MAX_LINE, input) && actual_count < count) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) continue;
        
        // Разбираем строку: фамилия имя год
        if (sscanf(line, "%s %s %d",
                   humans[actual_count].surname,
                   humans[actual_count].name,
                   &humans[actual_count].birth_year) == 3) {
            actual_count++;
        }
    }
    fclose(input);
    
    // LINK Выводим исходный массив
    printf("Исходный массив:\n");
    for (int i = 0; i < actual_count; i++) {
        printf("%s %s %d\n", 
               humans[i].surname, 
               humans[i].name, 
               humans[i].birth_year);
    }
    
    // LINK Сортируем по году рождения
    sort_by_year(humans, actual_count);
    
    // LINK Выводим отсортированный массив в консоль
    printf("\nОтсортированный по году рождения:\n");
    for (int i = 0; i < actual_count; i++) {
        printf("%s %s %d\n", 
               humans[i].surname, 
               humans[i].name, 
               humans[i].birth_year);
    }
    
    // LINK Записываем результат в файл
    FILE *output = fopen(outputFilePath, "w");
    if (!output) {
        fprintf(stderr, "Ошибка открытия %s\n", outputFilePath);
        return 1;
    }
    
    for (int i = 0; i < actual_count; i++) {
        fprintf(output, "%s %s %d\n", 
                humans[i].surname, 
                humans[i].name, 
                humans[i].birth_year);
    }
    fclose(output);

    printf("\nРезультат записан в %s\n", outputFilePath);

    free(humans);
    return 0;
}