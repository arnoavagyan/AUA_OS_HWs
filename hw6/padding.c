#include <stdio.h>

struct S
{
    int    b;
    double c;
    char   a;
};

int main() 
{
    struct S s;
    printf("Size of struct S: %zu bytes\n", sizeof(s));
    
    printf("Size of char   field of S struct: %zu bytes\n", sizeof(s.a));
    printf("Size of int    field of S struct: %zu bytes\n", sizeof(s.b));
    printf("Size of double field of S struct: %zu bytes\n", sizeof(s.c));

    printf("\n");

    printf("Address of the char   field of S struct: %p\n", (void*)&s.a);
    printf("Address of the int    field of S struct: %p\n", (void*)&s.b);
    printf("Address of the double field of S struct: %p\n", (void*)&s.c);

    
}