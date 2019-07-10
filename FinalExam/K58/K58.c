#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int Command(int argc, char *argv[]);
void ReadFile(FILE *fPtr, Graph graph);


int main(int argc, char*argv[])
{
    int i, id, id1, id2, choice, total, numOfOut, length;
    Graph graph = createGraph();
    FILE *fPtr;
    JRB node, tree;
    char nameBook[100];
    int output[100], path[100];

    if(argc == 2)
    {   if(strcmp(argv[1], "help") == 0)
            puts("Supported command: help, i2n, n2i, cc, ce, odg, rel.");
        else if(strcmp(argv[1], "about") == 0)
            puts("C Advanced 20142 final exam.");
        exit(1);
    }
    else if(argc > 2)
        fPtr = fopen(argv[2], "r");

    choice = Command(argc, argv);
    switch (choice)
    {
        case 1:
            id = atoi(argv[3]);
            ReadFile(fPtr, graph);

            node = jrb_find_int(graph.vertices, id);
            if(node != NULL)
                printf("%s\n", jval_s(node->val));
            break;

        case 2:
            ReadFile(fPtr, graph);

            jrb_traverse(node, graph.vertices)
            {
                if(strcmp(jval_s(node->val), argv[3]) == 0)
                    break;
            }
            printf("%d\n", jval_i(node->key));

            break;

        case 3:
            id1 = atoi(argv[3]);
            id2 = atoi(argv[4]);

            ReadFile(fPtr, graph);

            jrb_traverse(node, graph.vertices)
            {
                id = jval_i(node->key);
                if (hasEdge(graph, id1, id) && hasEdge(graph, id2, id))
                {
                    printf("%s\n", jval_s(node->val));
                }
            }

            break;

        case 4:
            id1 = atoi(argv[3]);
            id2 = atoi(argv[4]);

            ReadFile(fPtr, graph);

            jrb_traverse(node, graph.vertices)
            {
                id = jval_i(node->key);
                if (hasEdge(graph, id, id1) && hasEdge(graph, id, id2))
                {
                    printf("%s\n", jval_s(node->val));
                }
            }

            break;

        case 5:
            numOfOut = atoi(argv[3]);

            ReadFile(fPtr, graph);

            jrb_traverse(node, graph.vertices)
            {
                total = outdegree(graph, jval_i(node->key), output);

                if(total > numOfOut)
                    printf("%s\n", jval_s(node->val));
            }

            break;

        case 6:
            id = atoi(argv[3]);

            ReadFile(fPtr, graph);

            jrb_traverse(node, graph.vertices)
            {
                id1 = jval_i(node->key);
                total = shortestPath(graph, id, id1, path, &length);
                for (i = 0; i < length; i++)
                    printf("%d  ", path[i]);
                printf("\n");
                if (total != INFINITIVE_VALUE)
                    if (length == 2 || length == 3)
                        printf("%s\n", jval_s(node->val));
            }

            break;
    }



}

int Command(int argc, char *argv[])
{
    if(strcmp(argv[1], "i2n")==0)
        return 1;
    if (strcmp(argv[1], "n2i") == 0)
        return 2;
    if (strcmp(argv[1], "cc") == 0)
        return 3;
    if (strcmp(argv[1], "cr") == 0)
        return 4;
    if (strcmp(argv[1], "odg") == 0)
        return 5;
    if (strcmp(argv[1], "rel") == 0)
        return 6;
}

void ReadFile(FILE *fPtr, Graph graph)
{
    int i, j, id, id1, id2, numOfV, numOfE;
    char nameBook[100];

    fscanf(fPtr, "%d %d\n", &numOfV, &numOfE);

    for (i = 0; i < numOfV; i++)
    {
        fscanf(fPtr, "%[^ ] %d\n", nameBook, &id);
        addVertex(graph, id, nameBook);
    }
    for (i = 0; i < numOfE; i++)
    {
        fscanf(fPtr, "%d %d\n", &id1, &id2);
        addEdge(graph, id1, id2, 1);
    }

    fclose(fPtr);
}
