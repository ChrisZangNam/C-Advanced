#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int main()
{
    char *filename = "Bus1.txt";
    IS is = new_inputstruct(filename);
    Graph g;

    g = createGraph();
    int id = 0; //id cua diem bus

    if (is == NULL)
    {
        printf("File fail!\n");
        exit(1);
    }

    char *busLine;
     //ten tuyen bus
    //char *busLine[113]; //mang luu cac tuyen di qua mot diem bus
    while (get_line(is) > 0) //Doc tung dong trong file
    {
        if (strcmp(is->fields[0], "TUYEN") == 0)
        {
            char temp[6];
            fgets(temp, 6, is->f);
            fscanf(is->f, "%[^\n]\n", busLine);
            /*
            busLine = (char *)malloc(sizeof(char) * strlen(is->fields[1]) + 1); //Tach ten tuyen ra
            strcpy(busLine, is->fields[1]);*?
            continue;
        }

        int busStopNum = 0;              //So luong diem bus trong line
        for (int i = 0; i < is->NF; i++) //NF: so luong field trong line: so tu trong line
        {
            if (strcmp(is->fields[i], "-") == 0)
                busStopNum++; //Dem xem co bao nhieu ki tu - trong line
        }

        char *busStopName[++busStopNum]; //mang luu ten cac diem bus
        int j = 0;

        //  printf("%d\n", busStopNum);
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
    printBus(g);

    printf("Co %d diem bus.\n", getNumOfVertex(g));
    printf("Nhap id diem bus: ");
    scanf("%d", &id);
    printf("Ten diem bus la: %s\n", getVertex(g, id));

   /* char s1[100], s2[100];
    printf("Nhap ten 2 diem: ");
    gets(s1);
    gets(s2);
    printf("%d\n", hasEdge(g, s1, s2));
    char s1[100], s2[100];
    printf("Nhap ten 2 diem: ");
    gets(s1);
    gets(s2);
    printf("%d\n", hasEdge(g, s1, s2));*/
}
