#include <stdio.h>
#include <stdlib.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h" //Double linked list


typedef JRB Graph;

Graph createGraph()
{
    return make_jrb();
}

void addEdge_int(Graph graph, int v1, int v2)
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

void addEdge_str(Graph graph, char *s1, char *s2)
{
    Graph node1 = jrb_find_str(graph, s1);

    if (node1 == NULL)
    {
        Graph tree = make_jrb();
        jrb_insert_str(graph, s1, new_jval_v(tree));
        jrb_insert_str(tree, s2, new_jval_i(1));
    }
    else
    {
        Graph tree;
        tree = (JRB)jval_v(node1->val);
        jrb_insert_str(tree, s2, new_jval_i(1));
    }

    Graph node2 = jrb_find_str(graph, s2);

    if (node2 == NULL)
    {
        Graph tree = make_jrb();
        jrb_insert_str(tree, s1, new_jval_i(1));
    }
    else
    {
        Graph tree;
        tree = (JRB)jval_v(node2->val);
        jrb_insert_str(tree, s1, new_jval_i(1));
    }
}

int adjacent(Graph graph, int v1, int v2)
{
    Graph node1 = jrb_find_int(graph, v1);
    if (node1 == NULL)
        return 0;
    else
    {
        JRB tree = (JRB)jval_v(node1->val);
        if (jrb_find_int(tree, v2) == NULL)
            return 0;
        else
            return 1;
    }
}

int getAdjacentVertices(Graph graph, int v, int *output)
{
    Graph node = jrb_find_int(graph, v);
    if(node == NULL)
        return 0;
    Graph tree = (JRB)jval_v(node->val);
    int total = 0;
    jrb_traverse(node, tree)
        output[total++] = jval_i(node->key);

    return total;
}

void printVertex(int v)
{
    printf("%4d", v);
}

void BFS(Graph graph, int start, int stop, void(*func)(int))
{
    int visited[100] = {};
    int n, output[100], v, i, u;
    Dllist queue, node;

    queue = new_dllist();

    dll_append(queue, new_jval_i(start));

    while(!dll_empty(queue) )
    {
        node = dll_first(queue);
        u = jval_i(node->val);

        dll_delete_node(node);
        if(!visited[u])
        {
            func(u);
            visited[u] = 1;
            if(u == stop)
                return;
            n = getAdjacentVertices(graph, u, output);
            for (i = 0; i < n; i++)
            {
                v = output[i];
                if(!visited[v])
                    dll_append(queue, new_jval_i(v));
            }
        }
    }
}

void DFS(Graph graph, int start, int stop, void (*func)(int))
{
    int visited[100] = {};
    int output[100], i, v, u, n;
    Dllist node, stack;

    stack = new_dllist();
    dll_append(stack, new_jval_i(start));

    while(!dll_empty(stack))
    {
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);

        if(!visited[u])
        {
            visited[u] = 1;
            func(u);
            if(u == stop)
                return;

            n = getAdjacentVertices(graph, u, output);
            for (i = n-1; i >=0; i--)
            {
                v = output[i];
                if(!visited[v])
                    dll_append(stack, new_jval_i(v));
            }
        }
    }
}
