#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_Diem 100

int main()
{
    FILE *fPtr;
    Graph graph;

    graph = createGraph();
    fPtr = fopen("Bus1.txt", "r");
    char tuyen[100], str[10], tmp[1000];
    char diem1[100];
    char diem2[100];
    int i, j;
    int id = 0;
    int k;
   // char c;
    char s1[MAX_Diem], s2[MAX_Diem];

    while (!feof(fPtr))
    {
        fscanf(fPtr, "%[^\n]\n", tuyen);
        fscanf(fPtr, "%[^\n]\n", tmp);
        i = 0;
        while(tmp[i] != '\0')
        {
            j = 0;
            for (; i < strlen(tmp) && tmp[i] != '-'; i++)
            {
                diem1[j] = tmp[i];
                j++;
            }
            diem1[j] = '\0';
            if (jrb_find_str(graph.vertices, diem1) == NULL)
            {
                id++;
                addVertex(graph, strdup(diem1), id);
            }

            addEdge(graph, strdup(diem2), strdup(diem1), 1);
            strcpy(diem2, diem1);
            i++;
        }

        //Chieu ve
        fscanf(fPtr, "%[^\n]\n", tmp);
        i = 0;
        while (tmp[i] != '\0')
        {
            j = 0;
            for (; i < strlen(tmp) && tmp[i] != '-'; i++)
            {
                diem1[j] = tmp[i];
                j++;
            }
            diem1[j] = '\0';
            if (jrb_find_str(graph.vertices, diem1) == NULL)
            {
                id++;
                addVertex(graph, strdup(diem1), id);
            }

            addEdge(graph, strdup(diem2), strdup(diem1), 1);
            strcpy(diem2, diem1);
            i++;
        }

    }

    printf("Co %d diem bus.\n", id);

    // printBus(graph);
    printf("Nhap so hieu diem: ");
    scanf("%d", &k);
    char *name = getVertex(graph, k);
    printf("%s\n", name);/*
    printf("Nhap ten 2 diem: ");
    gets(s1);
    gets(s2);
    printf("%d\n", hasEdge(graph, s1, s2));
    fclose(fPtr);*/
    return 0;
}
