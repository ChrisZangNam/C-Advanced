#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "k60.h"
#include "libfdr/fields.h"
#include "libfdr/jrb.h"

void instruction();
void ReadFile1(char *filename, Graph graph);
void ReadFile2(char *filename, Graph graph);

int main()
{
    int choice;
    Graph graph;
    graph = createGraph();

    char *filename1 = "product.txt";
    char *filename2 = "orderhistory.txt";

    int path[100];
    int length;
    int a[100];
    int total;

    int id, i, j, id1, id2;

    instruction();
    printf("--> Nhap lua chon: ");
    scanf("%d", &choice);
    printf("\n\n");

    while (choice != 6)
    {
        switch(choice)
        {
            case 1:

                ReadFile1(filename1, graph);
                JRB node;

                jrb_traverse(node, graph.vertices)
                {
                    printf("Ma san pham: %d\n", jval_i(node->key));
                    printf("Ten san pham: %s\n", jval_s(node->val));
                    printf("\n");
                }

                printf("--------------------------------------------------\n");
                break;

            case 2:
                ReadFile2(filename2, graph);
                printf("--------------------------------------------------\n");
                break;

            case 3:
                printf("Nhap ma cua 2 san pham la: ");
                scanf("%d %d", &id1, &id2);
                int weight;

                if(hasEdge(graph, id1, id2))
                    weight = getEdgeValue(graph, id1, id2);
                else
                    weight = -1;

                printf("Do lien quan giua hai san pham la: %d\n", weight);

                printf("--------------------------------------------------\n");
                break;

            case 4:
                printf("Nhap ma san pham: ");
                scanf("%d", &id);
                int output[100];
                int total = outdegree(graph, id, output);


                printf("Cac san pham lien quan :");
                for (i = 0; i < total; i++)
                {
                    node = jrb_find_int(graph.vertices, output[i]);
                    printf("%s, ", jval_s(node->val));
                }
                printf("\n");

                printf("--------------------------------------------------\n");
                break;

            case 5:
                printf("Nhap ma so 2 san pham: ");
                scanf("%d %d", &id1, &id2);
                JRB node_v;

                total = shortestPath(graph, id1, id2, path, &length);

                if(total == INFINITIVE_VALUE)
                    puts("Khong ton tai duong di giua hai san pham");
                else
                {
                    for (i = 0; i < length-1; i++)
                    {
                        node_v = jrb_find_int(graph.vertices, path[i]);
                        printf("%s --> ", jval_s(node_v->val));
                    }
                    node_v = jrb_find_int(graph.vertices, path[length-1]);
                    printf("%s.\n", jval_s(node_v->val));
                }
                printf("--------------------------------------------------\n");
                break;

            default:
                puts("Khong ton tai lua chon da nhap !\nVui long nhap lai");
                printf("--------------------------------------------------\n");
                break;
            }
            instruction();
            printf("--> Nhap lua chon: ");
            scanf("%d", &choice);
            printf("\n\n");
    }
    printf("Ket thuc chuong trinh\n");
}

void instruction()
{
    printf("-------------MENU--------------\n");
    puts("1. In danh sach san pham\n"
         "2. In danh sach gio dich\n"
         "3. Hien thi muc do lien quan giua 2 san pham\n"
         "4. In danh sach cac san pham lien quan\n"
         "5. Hien thi moi lien he giua hai san pham\n"
         "6. Thoat\n");
}

void ReadFile1(char *filename, Graph graph)
{//So hang hoa
    int id;
    char nameOfH[100];
    FILE *fPtr = fopen(filename, "r");
    if(fPtr == NULL)
        puts("Can not open file.");

    while (!feof(fPtr))
    {
        fscanf(fPtr, "%d %s\n", &id, nameOfH);
        addVertex(graph, id, nameOfH);
    }

    fclose(fPtr);
}

void ReadFile2(char *filename, Graph graph)
{
    IS is = new_inputstruct(filename);
    int id, id1, id2, i, j;

    if(is == NULL)
        puts("Can not open file.");

    while(get_line(is) > 0)
    {
        for ( i = 0; i < is->NF; i++)
        {
            id = atoi(is->fields[i]);
            JRB node = jrb_find_int(graph.vertices, id);
            printf("%s ", jval_s(node->val));
        }

        for (i= 0; i < is->NF-1; i++)
        {
            id1 = atoi(is->fields[i]);
            for (j = i + 1; j < is->NF ; j++)
            {
                id2 = atoi(is->fields[j]);
                addEdge(graph, id1, id2, 1);
            }
        }
        printf("\n");
    }
}
