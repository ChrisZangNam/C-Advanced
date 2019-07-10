#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Use Adjacent Matrix
typedef struct{
    int *matrix;
    int sizemax;
} Graph;

Graph createGraph(int sizemax)
{
    Graph g;
    g.matrix = (int *)malloc(sizeof(int) * sizemax);
    g.sizemax = sizemax;

    for (int i = 0; i < sizemax; i++)
        g.matrix[i] = 0;

    return g;
}

void addEgde(Graph graph, int v1, int v2)
{
    int n = sqrt(graph.sizemax);
    int i = v1 * n + v2;
    int j = v2 * n + v1;
    graph.matrix[i] = 1;
    graph.matrix[j] = 1;
}

int adjacent(Graph graph, int v1, int v2)
{
    int n = sqrt(graph.sizemax);
    int i = v1 * n + v2;
    return graph.matrix[i];
}

int getAdjacentVertices(Graph graph, int vertex, int* output)
{
    int count = 0;
    int n = sqrt(graph.sizemax);

    for (int j = 0; j < n; j++)
    {
        int i = vertex * n + j;
        if (graph.matrix[i] == 1)
            output[count++] = j;
    }

    return count;
}

void dropGraph(Graph graph)
{
    graph.sizemax = 0;
    free(graph.matrix);
}

//Use Adjacent List

int main()
{
    int i, n, output[100];
    Graph g = createGraph(100);

    addEgde(g, 0, 1);
    addEgde(g, 0, 2);
    addEgde(g, 1, 2);
    addEgde(g, 1, 3);

    n = getAdjacentVertices(g, 2, output);

    if(n == 0)
        puts("No adjacent verticesog node 2");
   else
    {
        printf("Adjacent vertices of node 2: ");
        for (i = 0; i < n; i++)
            printf("%5d", output[i]);
        printf("\n");
    }
}
