#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef JRB Graph;



int main()
{
    Graph g = createGraph();

    addEdge_int(g, 0, 1);
    addEdge_int(g, 1, 2);
    addEdge_int(g, 1, 3);
    addEdge_int(g, 2, 4);
    addEdge_int(g, 4, 5);
   // addEdge_int(g, 3, 4);
   // addEdge_int(g, 4, 7);
    //addEdge_int(g, 5, 6);
//BFS
    printf("BFS start from node 1 to node 5 is: ");
    BFS(g, 1, 5, printVertex);
    printf("\nBFS start from node 1 to node all is: ");
    BFS(g, 1, -1, printVertex);
    printf("\n");
//DFS
    printf("DFS start from node 1 to node 5 is: ");
    DFS(g, 1, 5, printVertex);
    printf("\nDFS start from node 1 to node all is: ");
    DFS(g, 1, -1, printVertex);
    printf("\n");
}
