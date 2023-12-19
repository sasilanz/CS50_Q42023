

typedef struct node
{
    char *number;
    struct node *children[26];
}
node;


// single pointer to the root of the structure
node *trie;

