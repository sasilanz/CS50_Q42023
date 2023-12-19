#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;


int main(int argc, char *argv[])
{
    node *list = NULL;

    for (int = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n->number = number;
        n->next = NULL;

        n->next = list;
        list = n;
    }
    // introduction of a new pointer, which iterates over the linked list
    node *ptr = list;   // points to the first node in the list !!!

    // man könnte auch einen for-loop machen mit
    // for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

}
