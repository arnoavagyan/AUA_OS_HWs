#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 3;
    char **strings = malloc(n * sizeof(char *));
    if (strings == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        strings[i] = malloc(50 * sizeof(char));
        if (strings[i] == NULL)
        {
            printf("Memory allocation failed\n");
            // We have to free previously allocated memory before exiting
            for (int j = 0; j < i; j++)
            {
                free(strings[j]);
            }
            // We have to free the array of pointers as well
            free(strings);
            return 1;
        }
        printf("Enter string %d: ", i + 1);
        scanf("%s", strings[i]);
    }
    printf("All strings: ");
    for (int i = 0; i < n; i++)
    {
        printf("%s ", strings[i]);
    }
    printf("\n");
    
    strings = realloc(strings, (n+2) * sizeof(char *));
    if (strings == NULL)
    {
        printf("Memory reallocation failed\n");
        return 1;
    }
    for (int i = 0; i < 2; i++)
    {
        strings[n + i] = malloc(50 * sizeof(char));
        if (strings[n + i] == NULL)
        {
            printf("Memory allocation failed\n");
            // We have to free previously allocated memory before exiting
            for (int j = 0; j < n + i; j++)
            {
                free(strings[j]);
            }
            // We have to free the array of pointers as well
            free(strings);
            return 1;
        }
        printf("Enter additional string %d: ", n + i + 1);
        scanf("%s", strings[n + i]);
    }
    // We have added 2 more strings, so the numver of strings is now n + 2
    n += 2;
    printf("All strings after resizing: ");
    for (int i = 0; i < n; i++)
    {
        printf("%s ", strings[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        free(strings[i]);
    }
    free(strings);
    return 0;
}
