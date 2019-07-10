#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int Command(int argc, char *argv[]);
void ReadFile(FILE *fPtr, Graph graph, int m);
void ReadFile2(FILE *f1, FILE *f2, Graph graph, char *nameStore[], char *nameSp[]);


int main(int argc, char *argv[])
{
    int choice;
    FILE *fPtr, *f1, *f2, *f;
    int id1, id2, id3, num;

    char s[30];
    int id, m, n;
    char *nameSp[30];
    JRB node, node1,node2, tree, tree1, node_1, node_2;
    char *nameStore[10];


    int numOfH;
    int dist;
    float time = 30;

    Graph graph;
    graph = createGraph();

    if(argc > 3 && argc != 5)
    {
        f1 = fopen(argv[2], "r");
        f2 = fopen(argv[3], "r");
    }
    else if(argc == 3 || argc == 5)
        fPtr = fopen(argv[2], "r");
    else
    {
        printf("C-Advandced, HK 20182\n");
        exit(1);
    }


    choice = Command(argc, argv);

    switch (choice)
    {
    case 2:
        fscanf(fPtr, "%d\n", &m);
        while (!feof(fPtr))
        {
            fscanf(fPtr, "%[^ ]%*c%d\n", s, &id);
            printf("%s %d\n", s, id);
        }
        break;

    case 3:
        ReadFile(fPtr, graph, 4);
        id1 = atoi(argv[3]);
        id2 = atoi(argv[4]);

        printf("%d km\n", getEdgeValue(graph, id1, id2));
        break;

    case 4:
        ReadFile2(f1, f2, graph, nameStore, nameSp);

        jrb_traverse(node, graph.vertices)
        {
            id1 = jval_i(node->key);
            //printf("%d\n", id);
            printf("%s\n", nameStore[id1]);
            tree = (JRB)jval_v(node->val);
            jrb_traverse(node1, tree)
            {
                id2 = jval_i(node1->key);
                printf("%s %d\n",nameSp[id2], jval_i(node1->val));
            }
            printf("---\n");
        }

        break;

    case 5:
        ReadFile2(f1, f2, graph, nameStore, nameSp);

        id1 = atoi(argv[4]);//kho
        id2 = atoi(argv[5]);//san pham
       // printf("%d %d\n", id1, id2);

        node = jrb_find_int(graph.vertices, id1);
        printf("%s\n", nameStore[id1]);

        tree = (JRB)jval_v(node->val);
        node1 = jrb_find_int(tree, id2);
        printf("%s %d\n", nameSp[id2], jval_i(node1->val));

        printf("---Cac kho hang khac: \n");

        jrb_traverse(node2, graph.vertices)
        {
            id = jval_i(node2->key);
            if( hasEdge(graph, id1, id) == 1)
            {
                printf("%s\n", nameStore[id]);
                tree = (JRB)jval_v(node2->val);
                node1 = jrb_find_int(tree, id2);
                printf("%s %d\n", nameSp[id2], jval_i(node1->val));
            }
        }

        break;

    case 6:
        ReadFile2(f1, f2, graph, nameStore, nameSp);

        id = atoi(argv[4]);//id sp
        numOfH = atoi(argv[5]);//so luong hang dat
        id1 = atoi(argv[6]);//kho gan nhat
        id2 = atoi(argv[7]);//kho ke khi het hang

        node1 = jrb_find_int(graph.vertices, id1);
        tree = (JRB)jval_v(node1->val);
        node_1 = jrb_find_int(tree, id);
        if(jval_i(node_1->val) >= numOfH)
            printf("Dat hang thanh cong.\nThoi gian giao hang la %0.2f phut\n", time);
        else
        {
            node2 = jrb_find_int(graph.vertices, id2);
            tree1 = (JRB)jval_v(node2->val);
            node_2 = jrb_find_int(tree1, id);

            if(jval_i(node_1->val) + jval_i(node_2->val) >= numOfH)
            {
                dist = getEdgeValue(graph, id1, id2);
                //printf("%d\n", dist);
                time = 30 + ((float)dist / 30) * 60;
                printf("Dat hang thanh cong.\nThoi gian giao hang la %0.2f phut\n", time);
            }
            else
                printf("Dat hang khong thanh cong\n");
        }

        break;
    }

}

int Command(int argc, char *argv[])
{
    int i;
    if (strcmp(argv[0], "./qlykhang") != 0)
    {
        printf("File name is not correct.\n");
        exit(1);
    }
    if (argc == 3)
        return 2;
    if (argc == 5)
        return 3;
    if (argc == 4)
        return 4;
    if (argc == 6)
        return 5;
    if (argc == 8)
        return 6;
}

void ReadFile(FILE *fPtr, Graph graph, int m)
{
    int n;
    int id;
    char *name;
    int line = 1;
    int *type = malloc(sizeof(int) * (m+1));
    int i, v, a;
    int id1, id2, weight, numE;

    fscanf(fPtr, "%d\n", &n);

    while(!feof(fPtr))
    {
        if(line != (m+1)*n+1)
        {
            fscanf(fPtr, "%[^ ]%*c%d\n", name, &id);
            addVertex(graph, id, name);
            //printf("%d\n", id);
            for (i = 0; i < m; i++)
            {
                fscanf(fPtr, "%d %d\n", &v, &a);
                type[v] = a;
            }
            line = line + m + 1;
        }
        else
        {
            fscanf(fPtr, "%d\n", &numE);
            for (i = 0; i < numE; i++)
            {
                fscanf(fPtr, "%d %d %d\n", &id1, &id2, &weight);
                //printf("%d %d %d\n", id1, id2, weight);
                addEdge(graph, id1, id2, weight);
            }
        }
    }
}

void ReadFile2(FILE *f1, FILE *f2, Graph graph, char *nameStore[], char *nameSp[])
{
    int m,n,v,a, id1, id2, weight, numE, id;
    int i = 0;
    int line = 1;
    char nameK[30];
    char *name[30];

//file 2
    char s[30];
    fscanf(f2, "%d\n", &m);

    while (!feof(f2))
    {
        fscanf(f2, "%[^ ] %d\n", s, &i);
        nameSp[i] = (char *)malloc(sizeof(char) * strlen(s) + 1);
        strcpy(nameSp[i], s);
    }

    //file 1

    fscanf(f1, "%d\n", &n);

    while (!feof(f1))
    {
        if (line != (m + 1) * n + 1)
        {
            fscanf(f1, "%[^ ]%*c%d\n", nameK, &id);
            nameStore[id] = malloc(sizeof(char) * strlen(nameK) + 1);
            strcpy(nameStore[id], nameK);
            JRB tree;
            tree = make_jrb();
            for (i = 0; i < m; i++)
            {
                fscanf(f1, "%d %d\n", &v, &a);
                jrb_insert_int(tree, v, new_jval_i(a));
            }
            addVertex2(graph, id, tree);

            line = line + m + 1;
        }
        else
        {
            fscanf(f1, "%d\n", &numE);
            for (i = 0; i < numE; i++)
            {
                fscanf(f1, "%d %d %d\n", &id1, &id2, &weight);
                //printf("%d %d %d\n", id1, id2, weight);
                addEdge(graph, id1, id2, weight);
            }
        }
    }

    fclose(f1);
    fclose(f2);
}
