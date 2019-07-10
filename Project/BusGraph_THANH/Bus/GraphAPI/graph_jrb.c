#include "graph_jrb.h"
#include <stdlib.h>
#include <string.h>

Graph createGraph()
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}

void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

void addEdge(Graph graph, char *v1, char *v2)
{
    JRB node, tree;
    if (!hasEdge(graph, v1, v2))
    {
        node = jrb_find_str(graph.edges, v1);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_str(graph.edges, v1, new_jval_v(tree));
        }
        else
            tree = (JRB)jval_v(node->val);
        jrb_insert_str(tree, v2, new_jval_i(1));
    }
}

int hasEdge(Graph graph, char *v1, char *v2)
{
    JRB node, tree;
    node = jrb_find_str(graph.edges, v1);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    if (jrb_find_str(tree, v2) == NULL)
        return 0;
    else
        return 1;
}

int getAdjacentVertices(Graph graph, char *v, char *output[])
{
    JRB node = jrb_find_str(graph.edges, v);
    if (node == NULL)
        return 0;
    JRB tree = (JRB)jval_v(node->val);

    int total = 0;
    jrb_traverse(node, tree)
    {
        output[total] = (char *)malloc(sizeof(char) * strlen(jval_s(node->key)) + 1);
        strcpy(output[total], jval_s(node->key));
        total++;
    }
    return total;
}

void addVertex(Graph graph, char *id, char *name)
{
    JRB node = jrb_find_str(graph.vertices, id);
    JRB tree;
    if (node == NULL)
    {
        tree = make_jrb();
        jrb_insert_str(graph.vertices, id, new_jval_v(tree));
        // jrb_insert_str(graph.vertices, id, new_jval_s(strdup(name)));
    }
    else
        tree = (JRB)jval_v(node->val);

    node = jrb_find_str(tree, name);
    if (node == NULL)
        jrb_insert_str(tree, name, new_jval_i(1));
}

char *getVertex(Graph graph, int id)
{
    JRB ver = graph.vertices;
    JRB node;
    int i = 1;
    jrb_traverse(node, graph.vertices)
    {
        if (i == id)
            return jval_s(node->key);
        i++;
    }
}

int getNumofV(Graph graph)
{
    int count = 0;
    JRB node;
    jrb_traverse(node, graph.vertices)
        count++;
    return count;
}

int getNumofE(Graph graph)
{
    int count = 0;
    JRB node;
    jrb_traverse(node, graph.edges)
        count++;
    return count;
}

int shortest_noWeight_path(Graph graph, char *start, char *stop, char *path[])
{
    int V = getNumofV(graph);
    JRB dist = make_jrb();
    Dllist node;

    Dllist queue = new_dllist();
    dll_append(queue, new_jval_s(start));

    Dllist trace = new_dllist();
    dll_append(trace, new_jval_s(start));
    jrb_insert_str(dist, start, new_jval_v(trace));

    while (!dll_empty(queue))
    {
        node = dll_first(queue);
        char *u = (char *)malloc(sizeof(char) * strlen(jval_s(node->val)) + 1);
        strcpy(u, jval_s(node->val));
        dll_delete_node(node);

        Dllist u_find_path = jval_v(jrb_find_str(dist, u)->val);
        if (strcmp(u, stop) == 0)
        {
            int cnt = 0;
            Dllist tmp;
            dll_traverse(tmp, u_find_path)
            {
                cnt++;
                if (path != NULL)
                {
                    path[cnt - 1] = (char *)malloc(sizeof(char) * strlen(jval_s(tmp->val)) + 1);
                    strcpy(path[cnt - 1], jval_s(tmp->val));
                }
            }
            return cnt;
        }

        char *output[1000];
        int num = getAdjacentVertices(graph, u, output);
        for (int i = 0; i < num; ++i)
        {
            JRB v_find = jrb_find_str(dist, output[i]);
            if (v_find == NULL)
            {
                Dllist current_path = new_dllist();
                Dllist node;
                dll_traverse(node, u_find_path)
                    dll_append(current_path, node->val);

                dll_append(current_path, new_jval_s(output[i]));
                jrb_insert_str(dist, output[i], new_jval_v(current_path));
                dll_append(queue, new_jval_s(output[i]));
            }
        }
    }
}
