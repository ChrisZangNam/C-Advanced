#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int ReadFile(Graph graph, char *filename);
int ID(char s[]);
int ID_V(char s[]);
int E_Val(char s[]);
void instruction();
int V_Pre(Graph graph, int id, int V_pre[]);

int main()
{
    Graph graph = createGraph();
    char *filename = "data.txt";
    int numOfE = ReadFile(graph, filename);
    char work[4];
    int id, total, i, num_Work;
    char choice;
    int output[100], w_pre[100];
    JRB node;

    ReadFile(graph, filename);
//case 1
    printf("Cau 1:\n\tSo dinh: %d\n\tSo canh: %d\n", getNumOfV(graph), getNumOfE(graph));
//case 2
    do{
        printf("Cau 2: \n");
        printf("\tNhap vao mot cong viec bat ky: ");
        rewind(stdin);
        gets(work);
        id = ID(work);
        node = jrb_find_int(graph.vertices, id);
        if(node==NULL)
            puts("\tCong viec khong co trong chuong trinh.");
        else
        {
            total = outdegree(graph, id, output);
            printf("\tSo luong cong viec can lam ngay truoc %s la: %d\n", work, total);
            printf("\tDanh sach cac cong viec: ");
            for (i = 0; i < total; i++)
            {
                printf("A%d     ", output[i]);
            }
            printf("\n");

            num_Work = V_Pre(graph, id, w_pre);

            printf("\tSo luong tat ca cac cong viec can lam truoc %s la: %d\n", work, num_Work);
            printf("\tDanh sach cac cong viec: ");
            for (i = 0; i < num_Work; i++)
            {
                printf("A%d     ", w_pre[i]);
            }
            printf("\n");
        }
        //case 3
        printf("Cau 3: \n ");
        printf("Nguoi dung co muon tiep tuc thuc hien chuc nang 2 ? (y/n) ? ");
        scanf("%c%*c", &choice);
    } while (choice != 'n');

//case 4:
    printf("Cau 4: \n");
    printf("\tThu tu truoc sau cua danh sach cong viec la: ");
    topologicalSort(graph, output, &total);
    for (i = total-1; i >= 0; i--)
        printf("\tA%d", output[i]);
    printf("\n");

//case 5
    puts("Cau 5:");
    printf("\tNhap ten mot cong viec: ");
    rewind(stdin);
    gets(work);
    id = ID(work);



    printf("Thoi gian toi thieu de hoan thanh cong viec %s la: %d\n");

    //case 6:
    puts("Cau 6:");
    printf("\tKiem tra tinh hop le cua chu trinh\n");
    if(!DAG(graph))
        puts("\tDo thi co chu trinh ==> Khong hop le.");
    else
    {
        puts("\tDo thi khong co chu trinh ==> Hop le.");
    }
}

int ReadFile(Graph graph, char *filename)
{
    IS is = new_inputstruct(filename);

    if(is == NULL)
    {
        printf("Can not open file !\n");
        exit(0);
    }

    int id1, id2, e_value, i, total = 0;
    while(get_line(is) > 0)
    {
        id1 = ID(is->fields[0]);
        addVertex(graph, id1, is->fields);

        for (i = 2; i < is->NF; i++)
        {
            total++;
            id2 = ID_V(is->fields[i]);
            e_value = E_Val(is->fields[i]);
            addEdge(graph, id1, id2, e_value);
        }
    }

    return total;
}

int ID(char s[])
{
    int i;
    char name[10];
    for (i = 1; i < strlen(s); i++)
        name[i - 1] = s[i];
    name[i] = '\0';

    return atoi(name);
}

int ID_V(char s[])
{
    int i;
    char name_V[10];
    for (i = 1; i < strlen(s) && s[i] != '-'; i++)
        name_V[i - 1] = s[i];
    name_V[i] = '\0';

    return atoi(name_V);
}

int E_Val(char s[])
{
    int i, k;
    int j = 0;
    char e_val[10];

    for(i = 0; i < strlen(s) && s[i] != '-'; i++);
    k = i + 1;

    for (k; k < strlen(s); k++)
    {
        e_val[j] = s[k];
        j++;
    }
    e_val[j] = '\0';

    return atoi(e_val);
}

int V_Pre(Graph graph, int id, int V_pre[])
{
    int vistited[100] = {};
    int output[100];
    int u, count = 0;
    Dllist queue = new_dllist();
    dll_append(queue, new_jval_i(id));

    while(!dll_empty(queue))
    {
        Dllist node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);

        if(!vistited[u])
            V_pre[count++] = u;
        vistited[u] = 1;
        int n = outdegree(graph, u, output);
        for (int i = 0; i < n; i++)
        {
            int v = output[i];
            dll_append(queue, new_jval_i(v));
        }
    }
    return count;
}
