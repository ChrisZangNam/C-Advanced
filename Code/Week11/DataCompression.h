#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

#define INFINITIVE_VALUE 10000000
typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void dropGraph(Graph graph);
void addVertex(Graph graph, int id, char name);
char getVertex(Graph graph, int id);
int getVertexID(Graph graph, char c);
void addEdge(Graph graph, int v1, int v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2);

typedef struct
{
    Graph graph;
    JRB root;
} HuffmanTree;

typedef struct
{
    int size;
    char bits[10];
} Coding;

void insertQueue(JRB q, int id, int freq);
int findMinInQueue(JRB queue, int *freq);
void delInQueue(JRB queue, int id);
HuffmanTree makeHuffman(char *buffer, int size);
void find_code(HuffmanTree H, int ID, Coding htable[], char code[]);
void createHuffmanTable(HuffmanTree H, Coding htable[]);



void insertQueue(JRB q, int id, int freq)
{
    JRB node;

    node = jrb_find_int(q, id);
    if (node == NULL)
    {
        jrb_insert_int(q, id, new_jval_i(freq));
    }
    else
    {
        int newFreq = jval_i(node->val);
        newFreq += freq;
        node->val = new_jval_i(newFreq);
    }
}

int findMinInQueue(JRB queue, int *freq)
{
    JRB node;
    int min = INFINITIVE_VALUE;
    int id = 0;

    jrb_traverse(node, queue)
    {
        if (jval_i(node->val) < min)
        {
            min = jval_i(node->val);
            id = jval_i(node->key);
        }
    }

    *freq = min;
    return id;
}

void delInQueue(JRB queue, int id)
{
    JRB node;
    node = jrb_find_int(queue, id);
    jrb_delete_node(node);
}

HuffmanTree makeHuffman(char *buffer, int size)
{
    // Create a Huffman tree
    HuffmanTree H;
    H.graph.edges = make_jrb();
    H.graph.vertices = make_jrb();

    // Make a queue
    JRB queue = make_jrb();

    // Insert each character and its frequency into the queue
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        int id = getVertexID(H.graph, buffer[i]);
        if (id == 0)
        {
            count++;
            id = count;
            addVertex(H.graph, id, buffer[i]);
            insertQueue(queue, id, 1);
        }
        else
        {
            insertQueue(queue, id, 1);
        }
    }

    // Build the Huffman tree
    for (;;)
    {
        // Find the two smallest frequency in the queue
        int min1, min2;
        int freq1, freq2;
        min1 = findMinInQueue(queue, &freq1);
        delInQueue(queue, min1);
        min2 = findMinInQueue(queue, &freq2);
        if (min2 == 0)
            break;
        delInQueue(queue, min2);

        // Insert again into the queue with a sum frequency
        int id = count++;
        addEdge(H.graph, id, min1, 0);
        addEdge(H.graph, id, min2, 1);
        insertQueue(queue, id, freq1 + freq2);
    }

    int idRoot = count;
    H.root = jrb_find_int(H.graph.edges, idRoot);
}

// Run recurison to find a code for each charecter
void find_code(HuffmanTree H, int ID, Coding htable[], char code[])
{
    JRB node, tree, buf;
    char c;

    node = jrb_find_int(H.graph.edges, ID);
    if (node == NULL)
    {
        c = getVertex(H.graph, ID);
        strcpy(htable[c].bits, code);
        htable[c].size = strlen(code);
        printf("%c %s\n", c, htable[c].bits);
    }
    else
    {
        tree = (JRB)jval_v(node->val);
        jrb_traverse(buf, tree)
        {
            if (jval_i(buf->val) == 0)
                strcat(code, "0");
            else
                strcat(code, "1");
            find_code(H, jval_i(buf->key), htable, code);
            code[strlen(code) - 1] = '\0';
        }
    }
}

void createHuffmanTable(HuffmanTree H, Coding htable[])
{
    int i;
    char code[256] = "";

    for (i = 0; i < 256; i++)
        htable[i].size = 0;

    find_code(H, jval_i(H.root->key), htable, code);
}

void addVertex(Graph graph, int id, char name)
{
    JRB node = jrb_find_int(graph.vertices, id);
    if (node == NULL) // only add new vertex
        jrb_insert_int(graph.vertices, id, new_jval_c(name));
}

char getVertex(Graph graph, int id)
{
    JRB node = jrb_find_int(graph.vertices, id);
    if (node == NULL)
        return NULL;
    else
        return jval_c(node->val);
}

int getVertexID(Graph graph, char c)
{
    JRB node;

    jrb_traverse(node, graph.vertices)
    {
        if (jval_c(node->val) == c)
            return jval_i(node->key);
    }

    return 0;
}

// Make connection between v1 and v2
void addEdge(Graph graph, int v1, int v2, double weight)
{
    JRB node, tree;
    if (getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE)
    {
        node = jrb_find_int(graph.edges, v1);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        }
        else
        {
            tree = (JRB)jval_v(node->val);
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));
    }
}

// Get weight from v1 to v2
double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
    {
        return INFINITIVE_VALUE;
    }
    JRB tree = (JRB)jval_v(node->val);
    JRB node1 = jrb_find_int(tree, v2);
    if (node1 == NULL)
    {
        return INFINITIVE_VALUE;
    }
    return jval_d(node1->val);
}

Graph createGraph()
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}

void dropGraph(Graph graph)
{
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}
