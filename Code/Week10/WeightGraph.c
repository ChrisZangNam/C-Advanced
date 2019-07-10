#include <stdio.h>
#include <stdio.h>
#include "Graph.h"

int main()
{
    int i, s, t, length, path[1000];
    Graph g = createGraph();
    addVertex(g, "V1", 1);
    addVertex(g, "V2", 2);
    addVertex(g, "V3", 3);
    addVertex(g, "V4", 4);
    addVertex(g, "V5", 5);
    addVertex(g, "V6", 6);
    addVertex(g, "V7", 7);
    addVertex(g, "V8", 8);

    print(g);
    addEdge(g, 1, 2, 9);
    addEdge(g, 1, 6, 14);
    addEdge(g, 1, 7, 15);
    addEdge(g, 2, 3, 24);
    addEdge(g, 3, 5, 3);
    addEdge(g, 3, 8, 19);
    addEdge(g, 4, 3, 6);
    addEdge(g, 4, 8, 6);
    addEdge(g, 5, 4, 11);
    addEdge(g, 5, 8, 16);
    addEdge(g, 6, 3, 18);
    addEdge(g, 6, 5, 30);
    addEdge(g, 6, 7, 5);
    addEdge(g, 7, 5, 20);
    addEdge(g, 7, 8, 44);

    s = 1;
    t = 8;

    //printf("Weight of verter %d to %d is : %lf\n", 0, 1, getEdgeValue(g, 0, 1));

    double weight = shortedPath(g, s, t, path, &length);
    if (weight == INFINITIVE_VALUE)
        printf("No path between %d and %d\n", s, t);
    else
    {
        printf("Path between %d and %d: ", s, t);
        for (i = 0; i < length; i++)
            printf("%4d", path[i]);
        printf("\n");
        printf("Total weight: %f\n", weight);
    }

    dropGraph(g);
}
