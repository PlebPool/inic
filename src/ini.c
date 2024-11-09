#include "../include/ini.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char buf[100];
    return find_value("./test.ini", "testSection", "ok", buf, sizeof(buf));
}

int find_value(const char *restrict file_path, const char *restrict section,
               const char *key, char *buf, size_t buflen)
{
    FILE *file;
    char line_buffer[256];

    file = fopen(file_path, "r");
    if (file == NULL)
    {
        perror("Error reading file");
        return EXIT_FAILURE;
    }

    int i_fl = 0;
#define SECTION_FOUND (1 << 0)
#define VALUE_FOUND (1 << 1)
#define KEY_FOUND (1 << 2)
    char *token;
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL)
    {
        if (~i_fl & SECTION_FOUND)
        {
            token = strtok(line_buffer, "[]");
            if (strcmp(token, section) == 0)
                i_fl |= SECTION_FOUND;
            continue;
        }

        if (~i_fl & VALUE_FOUND)
        {
            token = strtok(line_buffer, "=");
            while (token != NULL)
            {
                if (strcmp(token, "\n") == 0)
                    break;

                if (~i_fl & KEY_FOUND)
                {
                    if (strcmp(token, key) == 0)
                        i_fl |= KEY_FOUND;
                    token = strtok(NULL, "=");
                    continue;
                }

                if (strlen(token) < buflen)
                {
                    printf("VALUE: %s\n", token);
                    i_fl |= VALUE_FOUND;
                }
                else
                {
                    return -1;
                }

                token = strtok(NULL, " =");
            }
        }
    }
    if (i_fl & VALUE_FOUND)
        return strlen(buf);
    return -1;
}
