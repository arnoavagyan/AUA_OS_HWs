#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter the n: ");
    scanf("%d", &n);
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
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    printf("Sum of elements is: %d\n", sum);
    free(arr);
    return 0;
}