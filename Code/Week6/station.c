#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "Graph.h"
typedef JRB Graph;



Graph readFile(FILE *fPtr)
{
    Graph g;
    g = createGraph();

    char *token1, *token2, *str, *s;
    fscanf(fPtr, "%s\n", str);
    while (strcpm(str, "[LINES]") != 0)
        fscanf(fPtr, "%s\n");

    while(!feof(fPtr))
    {
        fscanf(fPtr, "%3s", s);
        fscanf(fPtr, "%[^\n]", str);
        token1 = strtok(str, " ");

        while(token1 != NULL)
        {
            token2 = strtok(NULL, " ";)
            addEdge_str(g, token1, token2);
            strcpy(token1, token2);
        }
    }

    return g;
}

int getAdjacentStations(Graph graph, char *v, char *output[80][])
{
    Graph node = jrb_find_str(graph, v);
    Graph tree = (JRB)jval_v(node->val);
    int total = 0;
    jrb_traverse(node, tree)
        strcpy(output[][total++], jval_s(node->key));

    return total;
}

int main ()
{
    FILE *fPtr;
    fPtr = fopen("station.txt", "r");
    if(fPtr == NULL)
        puts("File not exist.");

    Graph g;
    char *str;

    strcpy(str, "S1");
    g = readFile(fPtr);
    int n = getAdjacentStations(g, str);
    printf("%D\n", n);z
}
