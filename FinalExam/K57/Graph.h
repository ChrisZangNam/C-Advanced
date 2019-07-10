#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h" //int linked list
#include "libfdr/fields.h"

#define INFINITIVE_VALUE 10000000

typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void addEdge(Graph graph, char *v1, char *v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);
double shortestPath(Graph graph, int s, int t, int *path, int *length);
void addVertex(Graph graph, char *code, char *name);
char *getVertex(Graph graph, char *id);
int hasEdge(Graph graph, char *v1, char *v2);
int DAG(Graph graph);
void topologicalSort(Graph graph, int *output, int *n);
void dropGraph(Graph graph);
int getNumOfV(Graph graph);
int getNumOfE(Graph graph);
char *convertToCode(Graph graph, char name[]);
