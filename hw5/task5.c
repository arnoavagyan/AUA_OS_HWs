#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    int* arr = malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        printf("Enter the grade for student %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    printf("The highest grade is: %d\n", max);

    int min = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    printf("The lowest grade is: %d\n", min);
    free(arr);
    return 0;
}