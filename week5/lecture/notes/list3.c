#include <stdio.h>
#include <stdlib.h>


// Jetzt wird keine fixes array gebaut, sondern ein pointer erzeugt
// welchem mit malloc entsprechend memory alloziiert wurde
// bei liste mit 3 integern 3 * grösse von int
int main(void)
{
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // in case i need more memory zb 4 int statt 3

    // HIER: use realloc and get rid of the byte per byte copying
    int *tmp = realloc(list, 4 * sizeof(int));
    // IMMER diesen check machen bei use of malloc
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }
    // liste (pointer) auf den neuen Wert von tmp setzten
    list = tmp;
    // adding the fourth value
    // tmp[3] = 4;
    list[3] = 4;

    // always free memory, wird hier aber nicht mehr gebraucht
    // free(list);


    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    free(list);
    return 0;
}
