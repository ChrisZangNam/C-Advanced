#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h" //Double linked list
#include "libfdr/fields.h"

typedef struct{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void dropGraph(Graph graph);
void printBus(Graph graph);
void addVertex(Graph graph, char *name, char *busLine);
char *getVertex(Graph graph, int id);
int hasEdge(Graph graph, char *v1, char *v2);
void addEdge(Graph graph, char *v1, char *v2);
int getNumOfVertex(Graph graph);
int getNumOfEdge(Graph graph);
int indegree(Graph graph, char *v, char *output[]);
int outdegree(Graph graph, char *v, char *output[]);
int getAdjacents(Graph graph, char *v);
int shortedPath(Graph graph, int s, int t, int *path, int *length); // return the total weight of the path and the path is given via path and its length.Return INFINITIVE_VALUE if no mpath is found

Graph createGraph()
{
    Graph graph;

    graph.edges = make_jrb();
    graph.vertices = make_jrb();

    return graph;
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

void addVertex(Graph graph, char *name, char *busLine)
{
    JRB node = jrb_find_str(graph.vertices, name);
    JRB tree;
    if (node == NULL)
    {
        tree = make_jrb();
        jrb_insert_str(graph.vertices, strdup(name), new_jval_v((void *)tree));
    }
    else
    {
        tree = (JRB)jval_v(node->val);
    }

    JRB node1 = jrb_find_str(tree, busLine);
    if(node1 == NULL)
        jrb_insert_str(tree, strdup(busLine), new_jval_i(1));
}


void printBus(Graph graph)
{
    JRB node;

        jrb_traverse(node, graph.vertices)
        {
            printf("%s\n", jval_s(node->key));
        }
}

char *getVertex(Graph graph, int id)
{
    JRB node;
    int i = 1;

    jrb_traverse(node, graph.vertices)
    {
        if(i == id)
           return jval_s(node->key);
        else
            i++;
    }

    return NULL;
}

int hasEdge(Graph graph, char *v1, char *v2)
{
    JRB node, tree;

    node = jrb_find_str(graph.edges, v1);
    if(node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    if(jrb_find_str(tree, v2) == NULL)
        return 0;
    else
        return 1;
}

void addEdge(Graph graph, char *v1, char *v2)
{
    JRB node, tree;
    if(!hasEdge(graph, v1, v2))
    {
        node = jrb_find_str(graph.edges, v1);
        if(node == NULL)
        {
            tree = make_jrb();
            jrb_insert_str(graph.edges, strdup(v1), new_jval_v(tree));
        }
        else
        {
            tree = (JRB)jval_v(node->val);
        }
        jrb_insert_str(tree, strdup(v2), new_jval_i(1));
    }
}

int getNumOfVertex(Graph graph)
{
    JRB node;
    int count = 0;

    jrb_traverse(node, graph.vertices)
    {
        count++;
    }
    return count;
}

int getNumOfEdge(Graph graph)
{
    JRB node;
    int count = 0;

    jrb_traverse(node, graph.edges)
    {
        count++;
    }
    return count;
}

int shortest_Path(Graph graph, char *s, char* t, char *path[])
{
    // Khoi tao cac distance = 0
    JRB distance; //Cay luu path, luu ten dinh duyet cung queue phia truoc
    distance = make_jrb();
    char *u; //Bien trung gian de lm cau
    Dllist queue, node; //queue de luu

    queue = new_dllist(); //
    dll_append(queue, new_jval_s(s));

    Dllist trace = new_dllist(); //truy vet: trace la mot queue luu lai duong di phia truoc = previous
    dll_append(trace, new_jval_s(s));
    jrb_insert_str(distance, s, new_jval_v(trace)); //trace la duong di den tung dinh s den dinh dang xet = previous(s)

    // Duyet Queue
    while (!dll_empty(queue))
    {
        node = dll_first(queue); //dequeue

        u = (char *)malloc(sizeof(char) * strlen(jval_s(node->val)) + 1);
        strcpy(u, jval_s(node->val));
        dll_delete_node(node);

        JRB temp = jrb_find_str(distance, u);
        Dllist u_find_path = jval_v(temp->val); //tim kiem trong dis gia tri dinh u, val la trace : queue luu duong

        if (strcmp(u, t) == 0)
        {
            //Truy vet lai path
            int count = 0; //bien dem so diem di qua
            Dllist tmp;//List luu path

            dll_traverse(tmp, u_find_path)
            {
                count++;
                if(path != NULL)
                {
                    path[count -1] = (char *)malloc(sizeof(char) * strlen(jval_s(tmp->val)) + 1);
                    strcpy(path[count - 1], jval_s(tmp->val));
                }
            }
            return count;
        }

        char *output[2000];

        int n = outdegree(graph, u, output); //Cac dinh ma u huong vao

        // Cap nhap distance cua tat ca cac dinh ma lien ke voi dinh min
        for (int i = 0; i < n; i++)
        {
            JRB vertex_find = jrb_find_str(distance, output[i]);

            if (vertex_find == NULL) //Chua tham vertex
            {
                Dllist cur_path = new_dllist(); //Luu duong di cho vertex_find tu s
                Dllist node1;
                dll_traverse(node1, u_find_path) //u_find_path la dinh phia truoc vua duyet o tren
                    dll_append(cur_path, node1->val);

                dll_append(cur_path, new_jval_s(output[i]));
                jrb_insert_str(distance, output[i], new_jval_v(cur_path));
                dll_append(queue, new_jval_s(output[i]));
            }
        }
    }
}

int indegree(Graph graph, char *v, char *output[])
{
    JRB tree, node;
    int total = 0;

    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        if(jrb_find_str(tree, v))
        {
            output[total] = (char *)malloc(sizeof(char) * strlen(jval_s(node->key)) + 1);
            output[total] = jval_s(node->key);
            total++;
        }
    }
    return total;
}

int outdegree(Graph graph, char *v, char *output[])
{
    JRB tree, node;
    int total = 0;

    node = jrb_find_str(graph.edges, v);

    if(node == NULL)
        return 0;

    tree = (JRB)jval_v(node->val);

    jrb_traverse(node, tree)
    {
        output[total] = (char *)malloc(sizeof(char) * strlen(jval_s(node->key)) + 1);
        strcpy(output[total], jval_s(node->key));
        total++;
    }
    return total;
}

int getAdjacents(Graph graph, char *v)
{
    JRB node;
    int count = 0;

    jrb_traverse(node, graph.vertices)
    {
        char *u = jval_s(node->key);

        if(hasEdge(graph, v, u) == 1 || hasEdge(graph, u, v) == 1)
        {
            printf("\t%2d. [%s]\n",count + 1, u);
            count++;
        }
    }
    return count;
}
