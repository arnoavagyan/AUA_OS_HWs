#include <stdio.h>

int main()
{
    int    x = 1;
    char   c = 'A';
    double d = 2.57;
    short  s = 4;
    printf("Size of int:    %zu bytes\n", sizeof(x));
    printf("Size of char:   %zu bytes\n", sizeof(c));
    printf("Size of double: %zu bytes\n", sizeof(d));
    printf("Size of short:  %zu bytes\n", sizeof(s));
    
    printf("\n");

    printf("Address of int    variable x: %p\n", (void*)&x);
    printf("Address of char   variable c: %p\n", (void*)&c);
    printf("Address of double variable d: %p\n", (void*)&d);
    printf("Address of short  variable s: %p\n", (void*)&s);
    return 0;
}