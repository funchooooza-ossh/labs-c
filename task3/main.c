#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/*
LINK
получает строку из ввода
работает в 2 режимах: с ограниченим размера и без
использует malloc для первичного выделения буффера и realloc для расширения и оптимизации
при ошибках работы с памятью exit(1), хотя можно return NULL
*/
char *getString(const char *prompt, int size)
{
    int capacity = (size > 0) ? (size + 1) : 16;
    int length = 0;
    char *buffer = (char *)malloc(capacity * sizeof(char));

    if (!buffer)
    {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    printf("%s", prompt);

    while(1)
    {
        int c = getchar();

        if (c == EOF)
        {
            if (length == 0)
            {
                free(buffer);
                exit(1);
            }

            break;
        }

        if (c == '\n')
        {
            break;
        }
        
        if (size == -1)
        {
            if (length + 1 >= capacity)
            {
                capacity *= 2;
                char *new_buffer = (char *)realloc(buffer, capacity);
                if (!new_buffer)
                {
                    free(buffer);
                    fprintf(stderr, "Ошибка расширения буффера\n");
                    exit(1);
                }
                buffer = new_buffer;
            }
            buffer[length++] = (char)c;
        }
        else
        {
            if (length < size)
            {
                buffer[length++] = (char)c;
            }
        }
    }
    buffer[length]  = '\0';

    char *buff = (char *)realloc(buffer, length + 1);
    return buff ? buff : buffer;
}

#define SIZE 80

int main()
{
    char *string = getString("Введите строку(макс. 80 символов):\n", SIZE);
    printf("Получена строка: %s\n", string);
    
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == 'a' || string[i] == 'b')
        {
            string[i] = toupper(string[i]);
        }
    }

    printf("Итоговая строка: %s\n", string);
    free(string);

    return 0;
}