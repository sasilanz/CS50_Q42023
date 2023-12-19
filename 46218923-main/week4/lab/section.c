#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int a = 28;
    int b = 50;
    int *c = &a;
    printf("1 *c=&a: a has the value %i, located at %p\n", a, &a);
    printf("1: b has the value %i, located at %p\n", b, &b);
    printf("1: c has the value %p, located at %p\n", c, &c);

    *c = 14;
    printf("2 *c=14: a has the value %i, located at %p\n", a, &a);
    printf("2: b has the value %i, located at %p\n", b, &b);
    printf("2: c has the value %p, located at %p\n", c, &c);

    c = &b;
    printf("3 c=&b: a has the value %i, located at %p\n", a, &a);
    printf("3: b has the value %i, located at %p\n", b, &b);
    printf("3: c has the value %p, located at %p\n", c, &c);

    *c = 25;
    printf("4 *c=25: a has the value %i, located at %p\n", a, &a);
    printf("4: b has the value %i, located at %p\n", b, &b);
    printf("4: c has the value %p, located at %p\n", c, &c);

    //printf("a has the value %i, located at %p\n", a, &a);
    //printf("b has the value %i, located at %p\n", b, &b);
    //printf("c has the value %p, located at %p\n", c, &c);
}
