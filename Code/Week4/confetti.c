#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"

typedef JRB Question;

int main()
{
    FILE *fPtr;
    fPtr = fopen("data.txt", "r");

    Question ques, node;
    int id;
    char key;
    char *str, *s;
    ques = make_jrb();

    //while(!feof(fPtr))
    //{
        fscanf(fPtr, "%d", &id);
        fscanf(fPtr, "%[^\n]\n", str);
        for (int i = 0; i < 4; i++)
        {
            fscanf(fPtr, "%[^\n]\n", s);
            strcat(str, s);
        }
        jrb_insert_int(ques, id, new_jval_s(str));
        key = fgetc(fPtr);
        jrb_insert_int(ques, id, new_jval_c(key));

      //  fscanf(fPtr, "\n\n", s);
    //}
}
