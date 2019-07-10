#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"

typedef JRB Graph;


Graph createGraph()
{
    return make_jrb();
}

void addEdge(Graph graph, int v1, int v2)
{
    Graph node1 = jrb_find_int(graph, v1);

    if (node1 == NULL)
    {
        Graph tree = make_jrb();
        jrb_insert_int(graph, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    else
    {
        Graph tree;
        tree = (JRB)jval_v(node1->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
    }

    Graph node2 = jrb_find_int(graph, v2);

    if (node2 == NULL)
    {
        Graph tree = make_jrb();
        jrb_insert_int(graph, v2, new_jval_v(tree));
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
    else
    {
        Graph tree;
        tree = (JRB)jval_v(node2->val);
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
}

int adjacent(Graph graph, int v1, int v2)
{
    Graph node1 = jrb_find_int(graph, v1);
    if(node1 == NULL)
        return 0;
    else
    {
        JRB tree = (JRB)jval_v(node1->val);
        if(jrb_find_int(tree, v2) == NULL)
            return 0;
        else
            return 1;
    }
}

int getAdjacentVertices(Graph graph, int v, int* output)
{
    Graph node = jrb_find_int(graph, v);
    Graph tree = (JRB)jval_v(node->val);
    int total = 0;
    jrb_traverse(node, tree)
        output[total++] = jval_i(node->key);

    return total;
}


int main()
{
    int i, n, output[100];
    Graph g = createGraph();

   addEdge(g, 0, 1);
   addEdge(g, 0, 2);
   addEdge(g, 1, 2);
   addEdge(g, 1, 3);

    n = getAdjacentVertices(g, 2, output);

    if (n == 0)
        puts("No adjacent verticesog node 2");
    else
    {
        printf("Adjacent vertices of node 2: ");
        for (i = 0; i < n; i++)
            printf("%5d", output[i]);
        printf("\n");
    }
    int check = adjacent(g, 0, 1);

    printf("check(0,1) = %d\n", check);
}
