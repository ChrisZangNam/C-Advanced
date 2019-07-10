#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"


void instruction();
void ReadFile(Graph graph, char *filename);
void printMatrix(Graph graph);
void printList(Graph graph);
int check3a(Graph graph, int id);
int maxIndegree(Graph graph);

int main()
{
    Graph graph;
    graph = createGraph();

    int i, j, choice, numOfV, total, id1, id2, length;
    int output[100];
    int path[100];
    JRB node;

    instruction();
    printf("Nhap lua chon: ");
    scanf("%d", &choice);
    printf("\n");

    while(choice != 0)
    {
        switch (choice)
        {
        case 1:
            ReadFile(graph, "dothi.txt");
            puts("Da doc xong file.\nMa tran ke cua do thi la: ");
            printMatrix(graph);
            puts("\n");
            break;

        case 2:
            printf("Danh sach ke cua cac thanh tri la:\n");
            printList(graph);
            puts("\n");
            break;

        case 3:
            //3a
            printf("\t3a. Danh sach cac thanh tri ma chi co the di den no truc tiep tu mot thanh khac\n\tbang cach di bo\n");
            numOfV = getNumOfV(graph);

            printf("\t--> Ket qua: ");
            for (i = 0; i < numOfV; i++)
            {
                if(check3a(graph, i+1))
                    printf("%5d", i + 1);
            }
            printf("\n");

            //3b
            printf("\t3b. Danh sach cac thanh tri co nhieu duong di noi truc tiep tu mot thanh tri khac den no nhat\n");
            printf("\t-->Ket qua: ");

            int max = maxIndegree(graph);
            for (i = 0; i < numOfV; i++)
            {
                total = outdegree(graph, i + 1, output);
                if (total == max)
                    printf("%5d", i + 1);
            }
            puts("\n\n");
            break;

        case 4:
            printf("Nhap thanh tri xuat phat s: ");
            scanf("%d", &id1);
            printf("Nhap thanh tri dich t: ");
            scanf("%d", &id2);

            total = shortestPath(graph, id1, id2, path, &length);

            if(total == INFINITIVE_VALUE)
                puts("ROUTE NOT FOUND");
            else
            {
                printf("--> Duong di ngan nhat tu %d den %d la: \n", id1, id2);
                printf("\tDo dai duong di: %d\n", total);
                printf("\tThu tu cac thanh tri: ");
                for (i = 0; i < length-1; i++)
                    printf("%d --> ", path[i]);
                printf("%d\n", path[length - 1]);
            }

            puts("\n");
            break;

        case 5:
            printf("Nhap thanh tri xuat phat s: ");
            scanf("%d", &id1);
            printf("Nhap thanh tri dich t: ");
            scanf("%d", &id2);

            total = shortestPath_5(graph, id1, id2, path, &length);

            if (total == INFINITIVE_VALUE)
                puts("ROUTE NOT FOUND");
            else
            {
                printf("--> Duong di ngan nhat tu %d den %d la: \n", id1, id2);
                printf("\tDo dai duong di: %d\n", total);
                printf("\tThu tu cac thanh tri: ");
                for (i = 0; i < length - 1; i++)
                    printf("%d --> ", path[i]);
                printf("%d\n", path[length - 1]);
            }

            puts("\n");
            break;

        default:
            puts("Khong ton tai lua chon.");
            break;
        }
        instruction();
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        printf("\n");
    }
    puts("Ket thuc chuong trinh.");
}

void instruction()
{
    puts("=======C-Advanced, HK 20182=======\n");
    puts("1. Doc file\n"
         "2. In ra danh sach ke moi thanh tri\n"
         "3. Dua ra\n"
         "\t3a. Danh sach thanh tri chi co the di truc tiep bang cach di bo\n"
         "\t3b. Danh sach cac thanh tri co nhieu duong di noi truc tiep den no nhat.\n"
         "4. Tim duong di ngan nhat\n"
         "5. Tim duong di bo ngan nhat\n"
         "0. Thoat chuong trinh\n");
}

void ReadFile(Graph graph, char *filename)
{
    FILE *fptr;
    fptr = fopen(filename, "r");
    if(fptr == NULL)
        puts("Khong ton tai file.");

    int numOfV, numOfE, i, j, weight, id1, id2;

    fscanf(fptr, "%d%*c%d\n", &numOfV, &numOfE);

    for (i = 0; i < numOfV; i++)
        addVertex(graph, i + 1, "");

    for (i = 0; i < numOfE; i++)
    {
        fscanf(fptr, "%d%*c%d%*c%d\n", &id1, &id2, &weight);
        addEdge(graph, id1, id2, weight);
    }
}

void printMatrix(Graph graph)
{
    int i, j, numOfV;
    numOfV = getNumOfV(graph);

    for (i = 0; i < numOfV; i++)
    {
        for (j = 0; j < numOfV; j++)
        {
            if(hasEdge(graph, i+1, j+1))
                printf("\t%d", getEdgeValue(graph, i+1, j+1));
            else
            {
                printf("\t0");
            }
                }
        printf("\n");
    }
}

void printList(Graph graph)
{
    int numOfV, i, j;
    numOfV = getNumOfV(graph);

    for (i = 0; i < numOfV; i++)
    {
        printf("\tCastle %d: ", i + 1);
        for (j = 0; j < numOfV; j++)
        {
            if(hasEdge(graph, i+1, j+1))
                printf("%d\t", j + 1);
        }
        printf("\n");
    }
}

int check3a(Graph graph, int id)
{
    int i, j;
    int output[100];
    int total;

    total = outdegree(graph, id, output);
    for (i = 0; i < total; i++)
    {
        if(getEdgeValue(graph, output[i], id) < 50)
        {
            return 0;
            break;
        }
    }

    return 1;
}

int maxIndegree(Graph graph)
{
    int numOfV, i, j;
    int output[100];
    int total, max = 0;
    numOfV = getNumOfV(graph);

    max = outdegree(graph, 1, output);

    for (i = 2; i <= numOfV; i++)
    {
        total = outdegree(graph, i, output);
        if(total > max)
            max = total;
    }

    return max;
}
