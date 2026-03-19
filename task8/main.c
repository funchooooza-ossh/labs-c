#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_LINE 256

#define inputFilePath "input.txt"
#define outputFilePath "output/output.txt"

// cтруктура человека
typedef struct {
    char name[MAX_NAME];
    char surname[MAX_NAME];
    int birth_year;
    char sex;  // 'М' или 'Ж'
    double height; // рост в метрах
} Human;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/// cравнивает двух людей по заданным полям
/// fields — строка с полями через пробел (например "year name gender height")
/// возвращает: -1 если a < b, 0 если равны, 1 если a > b
int compare_humans(const Human *a, const Human *b, const char *fields[]) {
    for (int i = 0; fields[i] != NULL; i++) {
        int cmp = 0;
        
        if (strcmp(fields[i], "year") == 0 || strcmp(fields[i], "году") == 0) {
            cmp = a->birth_year - b->birth_year;
        }
        else if (strcmp(fields[i], "name") == 0 || strcmp(fields[i], "имени") == 0) {
            cmp = strcmp(a->name, b->name);
        }
        else if (strcmp(fields[i], "surname") == 0 || strcmp(fields[i], "фамилии") == 0) {
            cmp = strcmp(a->surname, b->surname);
        }
        else if (strcmp(fields[i], "sex") == 0 || strcmp(fields[i], "полу") == 0) {
            cmp = a->sex - b->sex;
        }
        else if (strcmp(fields[i], "height") == 0 || strcmp(fields[i], "росту") == 0) {
            if (a->height < b->height) cmp = -1;
            else if (a->height > b->height) cmp = 1;
        }
        
        if (cmp != 0) return cmp;
    }
    return 0;
}

void sort_humans(Human arr[], int n, const char *fields[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare_humans(&arr[j], &arr[j + 1], fields) > 0) {
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
        fprintf(stderr, "Ошибка открытия input.txt\n");
        return 1;
    }
    
    // LINK Сначала считаем количество строк
    int count = 0;
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (ch == '\n') count++;
    }
    rewind(input); // возвращаемся в начало файла
    
    if (count == 0) {
        fprintf(stderr, "Файл пуст\n");
        return 1;
    }
    // LINK Выделяем память под массив
    Human *humans = (Human*)malloc(count * sizeof(Human));
    if (!humans) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }
    
    // LINK Читаем данные
    int actual_count = 0;
    char line[MAX_LINE];
    
    while (fgets(line, MAX_LINE, input) && actual_count < count) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) continue;
        
        // Разбиваем строку через strtok
        char *token = strtok(line, " ");
        if (!token) continue;
        strcpy(humans[actual_count].surname, token);
        
        token = strtok(NULL, " ");
        if (!token) continue;
        strcpy(humans[actual_count].name, token);
        
        token = strtok(NULL, " ");
        if (!token) continue;
        humans[actual_count].birth_year = atoi(token);
        
        token = strtok(NULL, " ");
        if (!token) continue;
        humans[actual_count].sex = token[0];
        
        token = strtok(NULL, " ");
        if (!token) continue;
        humans[actual_count].height = atof(token);
        
        actual_count++;
    }
    fclose(input);
    
    // LINK Выводим исходные данные
    printf("Исходные данные:\n");
    for (int i = 0; i < actual_count; i++) {
        printf("%s %s %d %c %.2f\n",
               humans[i].surname, humans[i].name,
               humans[i].birth_year, humans[i].sex,
               humans[i].height);
    }
    
    // LINK Ввод полей для сортировки
    printf("\nВведите поля для сортировки через пробел:\n");
    printf("Доступные поля: year, name, surname, sex, height\n\n");

    char input_fields[MAX_LINE];
    fgets(input_fields, MAX_LINE, stdin);
    input_fields[strcspn(input_fields, "\n")] = '\0';
    
    // Разбиваем строку на массив полей
    char *fields[10] = {NULL};
    int field_count = 0;
    char *token = strtok(input_fields, " ");
    
    while (token != NULL && field_count < 9) {
        fields[field_count++] = token;
        token = strtok(NULL, " ");
    }
    fields[field_count] = NULL;
    
    // LINK Сортируем
    sort_humans(humans, actual_count, (const char**)fields);
    
    // LINK Выводим результат
    printf("\nОтсортированные данные:\n");
    for (int i = 0; i < actual_count; i++) {
        printf("%s %s %d %c %.2f\n",
               humans[i].surname, humans[i].name,
               humans[i].birth_year, humans[i].sex,
               humans[i].height);
    }
    
    // LINK Записываем в файл
    FILE *output = fopen(outputFilePath, "w");
    if (!output) {
        fprintf(stderr, "Ошибка открытия %s\n", outputFilePath);
        free(humans);
        return 1;
    }
    
    for (int i = 0; i < actual_count; i++) {
        fprintf(output, "%s %s %d %c %.2f\n",
                humans[i].surname, humans[i].name,
                humans[i].birth_year, humans[i].sex,
                humans[i].height);
    }
    fclose(output);
    
    printf("\nРезультат записан в %s\n", outputFilePath);
    
    free(humans);
    return 0;
}