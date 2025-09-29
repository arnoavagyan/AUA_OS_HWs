#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter the n: ");
    scanf("%d", &n);
    
    int* arr = calloc(n, sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("Initial array elements are:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("Enter the value: ");
        scanf("%d", &arr[i]);
    }
    printf("Updated array elements are:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    float avg = 0;
    for (int i = 0; i < n; i++)
    {
        avg += arr[i];
    }
    avg /= n;
    printf("Average of elements is: %.1f\n", avg);

    free(arr);
    return 0;
}