#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{

    char str[20], code1[5], code2[5];
    double weight;

    strcpy(str, "HAN SGN 10.6");
    int i = 0, j = 0, k = 0;

    while (str[i] != ' ')
    {
        code1[i] = str[i];
        i++;
    }
    code1[i] = '\0';
    i++;
    while (str[i] != ' ')
    {
        code2[j] = str[i];
        i++;
        j++;
    }
    code2[j] = '\0';

    char wei[5];
    i++;
    while (str[i] != '\0')
    {
        wei[k] = str[i];
        i++;
        k++;
    }
    wei[k] = '\0';

    weight = atof(wei);

    printf("%s\n%s\n%lf\n", code1, code2, weight);
}
