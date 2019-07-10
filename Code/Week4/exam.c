#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

typedef JRB Question;

int main()
{
    FILE *fPtr;
    fPtr = fopen("data.txt", "r");

    Question node;
    long id;
    fscanf(fPtr, "%ld", &id);
    node->key = new_jval_l(id);
    printf("%ld\n", node->key.l);
}
