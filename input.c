
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

#define LINE_SIZE 64

static int readLine(char *buf, int size)
{
    int c;

    if (fgets(buf, size, stdin) == NULL)
    {
        return 0;
    }

    if (strchr(buf, '\n') == NULL)
    {
        c = getchar();
        if (c == EOF)
        {
            return 1;
        }
        while (c != '\n' && c != EOF)
        {
            c = getchar();
        }
        return 2;
    }

    return 1;
}

int readInt(const char *prompt, int min, int max)
{
    char buf[LINE_SIZE];
    char *end;
    long value;
    int status;

    while (1)
    {
        printf("%s", prompt);

        status = readLine(buf, LINE_SIZE);
        if (status == 0)
        {
            exit(0);  
        }
        if (status == 2)
        {
            printf("Input too long.\n");
            continue;
        }

        value = strtol(buf, &end, 10);

       
        if (end == buf || (*end != '\n' && *end != '\0'))
        {
            printf("Invalid number.\n");
            continue;
        }
        if (value < min || value > max)
        {
            printf("Enter a value from %d to %d.\n", min, max);
            continue;
        }
        return (int)value;
    }
}

float readFloat(const char *prompt, float min)
{
    char buf[LINE_SIZE];
    char *end;
    float value;
    int status;

    while (1)
    {
        printf("%s", prompt);

        status = readLine(buf, LINE_SIZE);
        if (status == 0)
        {
            exit(0);
        }
        if (status == 2)
        {
            printf("Input too long.\n");
            continue;
        }

        value = strtof(buf, &end);

        if (end == buf || (*end != '\n' && *end != '\0'))
        {
            printf("Invalid number.\n");
            continue;
        }
        if (value < min)
        {
            printf("Value must be at least %.2f.\n", min);
            continue;
        }
        return value;
    }
}

void readString(const char *prompt, char *dest, int size)
{
    int status;

    while (1)
    {
        printf("%s", prompt);

        status = readLine(dest, size);
        if (status == 0)
        {
            exit(0);
        }
        if (status == 2)
        {
            printf("Input too long. Maximum %d characters.\n", size - 1);
            continue;
        }

        dest[strcspn(dest, "\n")] = '\0';

        if (strlen(dest) > 0)
        {
            return;
        }
        printf("Input cannot be empty.\n");
    }
}
