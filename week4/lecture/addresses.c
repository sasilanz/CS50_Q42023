#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //string s = "HI!";
    char *s = "HI!";
    printf("%p\n", s);
    printf("%c\n", s[0]);  // or *s
    printf("%c\n", s[1]);  // or *s+1
    printf("%c\n", s[2]);  // or *s+2
}
