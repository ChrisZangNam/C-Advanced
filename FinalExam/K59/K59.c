 #include <stdio.h>
 #include <stdlib.h>
 #include "Graph.h"

int Command(int argc, char *argv[]);
int ReadFile1(FILE *fPtr, Graph graph);
int getAdjacents2V(Graph graph, int v1, int v2, int *output);
int check(int output[], int key, int k);
void ReadFile2(Graph graph, int ID[], int numID);

int main(int argc, char *argv[])
{
    int choice, id, id1, id2, numOfId, i, j;
    FILE *fPtr;
    Graph graph;
    graph = createGraph();
    JRB node, tree;
    int length, total;
    int path[100];
    int output[100];
    int ID[100];

    if (argc > 2)
        fPtr = fopen(argv[2], "r");
    else
        printf("C-Advanced, HK20152\n");

    choice = Command(argc, argv);

    switch(choice)
    {
        case 2:
            numOfId = ReadFile1(fPtr, graph);

            jrb_traverse(node, graph.vertices)
            {
                printf("%d %s\n", jval_i(node->key), jval_s(node->val));
            }

            break;

        case 3:
            id1 = atoi(argv[3]);
            id2 = atoi(argv[4]);

            numOfId = ReadFile1(fPtr, graph);
            if(!hasEdge(graph, id1, id2))
                printf("%d\n", getEdgeValue(graph, id1, id2));
            else
            {
                puts("-1");
            }

            break;

        case 4:
            id1 = atoi(argv[3]);
            id2 = atoi(argv[4]);

            numOfId = ReadFile1(fPtr, graph);

            total = shortestPath(graph, id1, id2, path, &length);

            printf("%d\n", total);

            for (i = 0; i < length; i++)
            {
                node = jrb_find_int(graph.vertices, path[i]);
                printf("%s\n", jval_s(node->val));
            }

            break;

        case 5:
            id = atoi(argv[3]);
            numOfId = ReadFile1(fPtr, graph);

            total = outdegree(graph, id, output);
            printf("%d\n", total);
            for (i = 0; i < total; i++)
            {
                node = jrb_find_int(graph.vertices, output[i]);
                printf("%d %s\n", jval_i(node->key), jval_s(node->val));
            }
            break;

        case 6:
            for (i = 0; i < argc - 3; i++)
            {
                ID[i] = atoi(argv[i+3]);
            }

            numOfId = ReadFile1(fPtr, graph);
            ReadFile2(graph, ID, argc - 3);

            break;
    }
}

int Command(int argc, char *argv[])
{
    int i;
    if (strcmp(argv[0], "./p") != 0)
    {
        printf("Command not exist.\n");
        exit(1);
    }if(argc == 3)
        return 2;
    if (argc == 4)
        return 5;
    if (argc >= 5)
    {
        if(strcmp(argv[1], "-w") == 0)
            return 3;
        if (strcmp(argv[1], "-p") == 0)
            return 4;
        if (strcmp(argv[1], "-s") == 0)
            return 6;
    }
}

int ReadFile1(FILE *fPtr, Graph graph)
{
    int id, numOfE, numOfId;
    char IP[20];
    int id1, id2, weight;

    fscanf(fPtr, "%d\n", &numOfId);
    for (int i = 0; i < numOfId; i++)
    {
        fscanf(fPtr, "%d %s\n", &id, IP);
        addVertex(graph, id, IP);
    }

    fscanf(fPtr, "%d\n", &numOfE);
    while(!feof(fPtr))
    {
        fscanf(fPtr, "%d %d %d\n", &id1, &id2, &weight);
        addEdge(graph, id1, id2, weight);
    }

    fclose(fPtr);

    return numOfId;
}

void ReadFile2(Graph graph, int ID[], int numID)
{
    int numE = 0;
    int i, j;

    printf("%d\n", numID);
    JRB node;

    for (i = 0; i< numID; i++)
    {
        node = jrb_find_int(graph.vertices, ID[i]);
        printf("%d %s\n", jval_i(node->key), jval_s(node->val));
    }

    for (i = 0; i< numID-1; i++)
        for (j = i + 1; j < numID; j++)
            if(hasEdge(graph, ID[i], ID[j]))
                numE++;
    printf("%d\n", numE);

    for (i = 0; i < numID - 1; i++)
        for (j = i + 1; j < numID; j++)
            if (hasEdge(graph, ID[i], ID[j]))
                printf("%d %d %d\n", ID[i], ID[j], getEdgeValue(graph, ID[i], ID[j]));
}
