#ifndef GRAPH_JRB_H
#define GRAPH_JRB_H

#include "../libfdr/dllist.h"
#include "../libfdr/fields.h"
#include "../libfdr/jval.h"
#include "../libfdr/jrb.h"

#define true 1
#define false 0
#define UNDIRECTED 0
#define DIRECTED 1
#define INT_MAX 2147483647

typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void dropGraph(Graph);
void addEdge(Graph graph, char *v1, char *v2);
int hasEdge(Graph graph, char *v1, char *v2);
int getNumofE(Graph);
int getAdjacentVertices(Graph graph, char *v, char *output[]);//Edge!

void addVertex(Graph graph, char *id, char *name);
char *getVertex(Graph graph, int id);
int getNumofV(Graph);

int shortest_noWeight_path(Graph graph, char *start, char *stop, char *path[]);

#endif /* GRAPH_JRB_H */
