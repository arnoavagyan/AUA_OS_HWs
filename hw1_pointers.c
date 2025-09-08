#include <stdio.h>

void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    // Part 1:
    printf("%s\n", "Part 1:");
    int  x = 5;
    int* p = &x;
    printf("%p\n", &x);
    printf("%p\n", p);
    *p = 7;
    printf("%d\n", x);
    printf("%d\n", *p);

    printf("\n");

    // Part 2:
    printf("%s\n", "Part 2:");
    int arr[5];
    // Initializing
    for (int i = 0; i < 5; i++) 
    {
        arr[i] = i;
    }
    // Printing using pointers
    for (int i = 0; i < 5; i++) 
    {
        printf("%d ", *(arr + i));
    }
    printf("\n");
    // Modifying using pointers
    for (int i = 0; i < 5; i++) 
    {
        *(arr + i) = 10 * i;
    }
    // Printing after the modification using pointers
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", *(arr + i));
    }
    printf("\n");
    // Printing after the modification using name
    for (int i = 0; i < 5; i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // Part 3:
    printf("%s\n", "Part 3:");
    int a = 3;
    printf("%s%d\n", "Value of the first argument before swap: ", a);
    int b = 7;
    printf("%s%d\n", "Value of the second argument before swap: ", b);
    swap(&a, &b);
    printf("%s%d\n", "Value of the first argument after swap: ", a);
    printf("%s%d\n", "Value of the second argument after swap: ", b);

    printf("\n");

    // Part 4:
    printf("%s\n", "Part 4:");
    int g = 7;
    p = &g;
    int** pp = &p;
    printf("%d\n", *p);
    printf("%d\n", **pp);

    printf("\n");

    // Part 5:
    printf("%s\n", "Part 5:");
    char str[] = "Hello";
    char* c = str;
    // Printing using pointers
    for (int i = 0; i < 5; i++) 
    {
        printf("%c", *(c + i));
    }
    unsigned int len = 0;
    while (*(c + len) != '\0') 
    {
        len++;
    }
    printf("\n");
    printf("%s%d", "Length of the string: ", len);
}