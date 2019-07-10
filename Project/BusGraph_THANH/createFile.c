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
    if (fPtr == NULL)
        puts("Not open file.");

    char busLine[50], del[6], tmp[1000];
    char *busStop1;
    char *busStop2;
    const char s[2] = "-";
    int id = 0;
    char s1[100], s2[100];

    while (!feof(fPtr))
    {
        fgets(del, 6, fPtr);
        fscanf(fPtr, "%[^\n]\n", busLine);
        //Chieu di
        fscanf(fPtr, "%[^\n]\n", tmp);

        busStop1 = strtok(tmp, s);

        while (busStop1 != NULL)
        {
            addVertex(graph, strdup(busStop1), busLine);
            busStop2 = malloc(sizeof(char) * 100);
            addEdge(graph, busStop2, busStop1);

            strcpy(busStop2, busStop1);
            busStop1 = strtok(NULL, s);
        }

        //chieu ve
        fscanf(fPtr, "%[^\n]\n", tmp);

        busStop1 = strtok(tmp, s);
        while (busStop1 != NULL)
        {
            addVertex(graph, strdup(busStop1), busLine);
            busStop2 = malloc(sizeof(char) * 100);
            addEdge(graph, busStop2, busStop1);

            strcpy(busStop2, busStop1);
            busStop1 = strtok(NULL, s);
        }
    }

    printBus(graph);
    fclose(fPtr);
    printf("Co %d diem bus.\n", getNumOfVertex(graph));

    printf("Nhap ten 2 diem: ");
    gets(s1);
    gets(s2);
    printf("%d\n", hasEdge(graph, s1, s2));

    fclose(fPtr);
}
