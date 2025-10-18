#include <stdio.h>

#pragma pack(4)
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

    printf("Address of the char   field of S struct: %p\n", (void*)&s.a);
    printf("Address of the int    field of S struct: %p\n", (void*)&s.b);
    printf("Address of the double field of S struct: %p\n", (void*)&s.c);

    return 0;
}