#include <stdio.h>
#include <string.h>

int main()
{
    char s[10];
    strcpy(s, "A2-10");

    int i = 0;
    int k;
    int j = 0;
    char e_val[10];

    for (i = 0; i < strlen(s) && s[i] != '-'; i++)
        ;

    for (k = i+1; k < strlen(s); k++)
    {
        e_val[j] = s[k];
        j++;
    }
    e_val[j] = '\0';
    printf("%s\n", e_val);
}
