#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");
    // eigentlich ist "string" char *s =

    char *t = malloc(strlen(s) + 1);
    // eigentlich char *t - es wird nur der pointer zur adresse von s kopiert

    // jetzt wird jeder einzelne char von string s zu t kopiert, strlen(s) + 1 wegen /0 am Ende jedes Strings
    // ODER: statt dem for loop strcpy(t, s)
    for (int i = 0; i < strlen(s) + 1; i++).
    {
        t[i] = s[i];
    }
    // sicherstellen, dass der reservierte memory platz auch wirklich inhalt hat
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);  // wird in s UND t geändert zu topupper, weil es s und t nur einmal gibt
    }
    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);
    return 0;
}

