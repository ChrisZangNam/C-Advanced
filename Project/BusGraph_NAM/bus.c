#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define max 1000
#define sizemax 1000

void readData(Graph g, char *filename);
void instruction();

int main()
{
    int key = 1, size, total, id, i;
    char name[max], s1[max], s2[max];
    //char *output[max];

    char *filename = "bus.txt";
    Graph graph;

    graph = createGraph();

    readData(graph, filename);

    instruction();
    printf("Nhap lua chon cua ban: ");
    scanf("%d%*c", &key);

    while (key != 0)
    {
        switch (key)
        {
        case 1:
            printf("\n\t____Ten mot dia diem trong Ha Noi___\n\n");
            printf("Nhap so hieu diem diem muon tim ten: ");
            scanf("%d%*c", &id);
            size = getNumOfVertex(graph);
            if(id > size || id <= 0)
                printf("Khong ton tai so hieu diem %d\nSo hieu diem nam trong doan tu 1 den %d\n", id, size);
            else
                printf("Ten cua dia diem %d la: \n\t[%s]\n", id, getVertex(graph, id));
            printf("\n============================================================\n");
            break;
        case 2:
            printf("\n\t___Kiem tra hai diem co noi truc tiep voi nhau___\n\n");
            puts("Nhap ten 2 diem ban muon kiem tra: ");
            printf("\tDiem 1: ");
            gets(s1);
            printf("\tDiem 2: ");
            gets(s2);

            if(hasEdge(graph, s1, s2) == 1 || hasEdge(graph, s2, s1) == 1)
                puts("---> Hai diem tren noi truc tiep voi nhau");
            else
                puts("---> Hai diem trem khong noi truc tiep voi nhau");
            printf("\n============================================================\n");
            break;

        case 3:
            puts("\n\t___Cac dia diem noi truc tiep voi mot dia diem___\n");

            printf("Nhap ten diem: ");
            rewind(stdin);
            gets(name);
            JRB node = jrb_find_str(graph.vertices, name);

            if (node == NULL)
                printf("Khong ton tai ten dia diem [%s]\n", name);
            else
            {
                printf("---> Cac dia diem noi truc tiep voi [%s] la: \n", name);

                total = getAdjacents(graph, name);
               // printf("--> Co %d diem noi truc tiep\n", total);
            }

            printf("\n============================================================\n");
            break;

        case 4:
            puts("\n\t___Tim duong di ngan nhat giua hai dia diem___\n");
            puts("Nhap ten hai dia diem: ");
            printf("\tDiem 1: ");
            rewind(stdin);
            gets(s1);
            printf("\tDiem 2: ");
            rewind(stdin);
            gets(s2);

            if(jrb_find_str(graph.vertices, s1) == NULL)
            {   printf("Khong ton tai diem [%s]\n", s1);
                break;
            }
            if(jrb_find_str(graph.vertices, s2) == NULL)
            {
                printf("Khong ton tai diem [%s]\n", s2);
                break;
            }

            char *path[2000];
            int num_path = shortest_Path(graph, s1, s2, path);

            printf("\n*** Duong di ngan nhat giua [%s] va [%s] la:  \n", s1, s2);

            for (i = 0; i < num_path; i++)
            {
                printf("[%s] ", path[i]);
                if(i < num_path - 1)
                    printf("--> ");
            }
            printf("\n");
            puts("\n*** Lo trinh tuyen can di \n");

            for (i = 0; i < num_path-1; i++)
            {
                printf("*[%s] --> [%s]: \n", path[i], path[i+1]);

                JRB node1 = jrb_find_str(graph.vertices, path[i]);
                JRB node2 = jrb_find_str(graph.vertices, path[i + 1]);

                JRB tree1 = (JRB)jval_v(node1->val);
                JRB tree2 = (JRB)jval_v(node2->val);

                printf("Tuyen di qua \n");
                JRB node;

                jrb_traverse(node, tree1)
                {
                    if(jrb_find_str(tree2, jval_s(node->key)) != NULL)
                        printf("\t%s\n", jval_s(node->key));
                }

            }

            printf("\n============================================================\n");
            break;

        case 5:
            printf("\n\t ke cac tuyen bus di qua mot diem___\n\n");
            printf("Nhap ten diem: ");
            rewind(stdin);
            gets(name);

            JRB node_Find = jrb_find_str(graph.vertices, name);
            if(node_Find == NULL)
                printf("Khong ton tai ten diem: %s\n", name);
            else
            {
                printf("Cac tuyen bus di qua diem: %s la: \n", name);
                JRB tree = (JRB)jval_v(node_Find->val);
                JRB node;

                jrb_traverse(node, tree)
                    printf("\t%s\n", jval_s(node->key));
            }


            printf("\n============================================================\n");
            break;

        default:
            puts("Khong ton tai lua chon cua ban !\nVui long nhap lai !\n");
            instruction();
            break;
        }
        instruction();
        printf("Nhap lua chon cua ban: ");
        scanf("%d%*c", &key);
    }
    printf("Ket thuc chuong trinh !\n");
    printf("\n============================================================\n");

    return 0;
}

void readData(Graph g, char *filename)
{
    IS is = new_inputstruct(filename);

    if (is == NULL)
    {
        printf("File fail!\n");
        exit(1);
    }

    char *busLine;//ten tuyen

    while (get_line(is) > 0) //Doc tung dong trong file
    {
        if (strcmp(is->fields[0], "TUYEN") == 0) //kiem tra dong chua ten tuyen
        {
            busLine = (char *)malloc(sizeof(char) * strlen(is->fields[1]) + 1); //Tach ten tuyen ra
            strcpy(busLine, is->fields[1]);
            continue;
        }

        int busStopNum = 0;              //So luong diem bus trong line
        for (int i = 0; i < is->NF; i++) //NF: so luong field trong line: so tu trong line
        {
            if (strcmp(is->fields[i], "-") == 0)
                busStopNum++; //Dem xem co bao nhieu ki tu - trong line
        }

        char *busStopName[++busStopNum]; //mang luu ten cac diem bus
        int j = 0; //bien chay de luu cac field vao busStop

        busStopName[j] = (char *)malloc(sizeof(char) * 100);
        for (int i = 0; i < is->NF; i++)
        {
            if (strcmp(is->fields[i], "-") == 0)
            {
                j++; //thu tu diem bus trong line
                busStopName[j] = (char *)malloc(sizeof(char) * 100);
                continue;
            }
            else
            {
                strcat(busStopName[j], is->fields[i]);
                if (i < is->NF - 1)
                    if (strcmp(is->fields[i + 1], "-") != 0)
                        strcat(busStopName[j], " ");
            }
        }

        for (int i = 0; i < busStopNum; i++)
            addVertex(g, busStopName[i], busLine);
        for (int i = 0; i < busStopNum - 1; i++)
            addEdge(g, busStopName[i], busStopName[i + 1]);
    }
}

void instruction()
{
    printf("============================================================\n");
    printf("\n|  ********CHUONG TRINH TIM DUONG DI XE BUS HA NOI*******  |\n\n");
    printf("============================================================\n\n");
    puts("  [ 0 ] Thoat khoi chuong trinh                              \n");
    puts("  [ 1 ] Ten cua mot dia diem trong Ha Noi                    \n");
    puts("  [ 2 ] Kiem tra hai dia diem co noi truc tiep voi nhau khong\n");
    puts("  [ 3 ] Cac dia diem noi truc tiep voi mot dia diem          \n");
    puts("  [ 4 ] Tim duong di ngan nhat giua hai dia diem             \n");
    puts("  [ 5 ] Liet ke tat ca cac tuyen bus di qua mot diem         \n");
    printf("============================================================\n");
}
