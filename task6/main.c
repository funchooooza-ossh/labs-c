#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

#define inputFilePath "input.txt"
#define outputFilePath "output/output.txt"
#define targetBirthYear 1980

int main()
{
    FILE *input = fopen(inputFilePath, "r");
    FILE *output = fopen(outputFilePath, "w");

    if (!input || !output)
    {
        fprintf(stderr, "Ошибка открытия файла\n");
        return 1;
    }
    char line[MAX_LINE];
    int count = 0;

    while (fgets(line, MAX_LINE, input))
    {
        // LINK заменяем перенос строки на нуль-терминатор
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) continue;
        
        // LINK находим последний пробел в строке
        char  *last_space = strrchr(line, ' ');
        if (!last_space) continue;
        
        // LINK конвертируем текст после последнего пробела в int
        int year = atoi(last_space + 1);

        if (year > targetBirthYear)
        {
            fprintf(output, "%s\n", line);
            count ++;
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}