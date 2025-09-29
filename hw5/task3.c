#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 10;
    int* arr = malloc(n * sizeof(int));
    if (arr == NULL) 
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i < n; i++) 
    {
        printf("Enter the value: ");
        scanf("%d", &arr[i]);
    }
    arr = realloc(arr, 5 * sizeof(int));
    if (arr == NULL) 
    {
        printf("Memory reallocation failed\n");
        return 1;
    }
    printf("Array after resizing: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}