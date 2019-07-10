#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/fields.h"
#include "GraphAPI/graph_jrb.h"

void inputDataFromTxt(Graph g, char filename[]);

int main()
{
    Graph g = createGraph();
    char filename[] = "hanoibus.txt";
    inputDataFromTxt(g, filename);

    JRB node;
    char *findBusPlace = (char *)malloc(sizeof(char) * 100);
    int selection;
    do
    {
        printf("\n****** Chuong Trinh Tim Duong Di Xe Bus Ha Noi ******\n"
               "0. Thoat khoi chuong trinh\n"
               "1. Ten cua mot dia diem trong Ha Noi\n"
               "2. Kiem tra hai dia diem co noi truc tiep voi nhau khong\n"
               "3. Cac dia diem noi truc tiep voi mot dia diem\n"
               "4. Tim duong di ngan nhat giua hai diem\n"
               "5. Liet ke cac tuyen xe bus di qua 1 diem\n"
               "---> Chon: ");
        scanf("%d", &selection);

        switch (selection)
        {
        case 0:
            printf("Thoat chuong trinh!\n");
            break;

        case 1:
        {
            printf("Nhap so hieu diem muon tim kiem: ");
            int findID;
            scanf("%d", &findID);
            if (findID > getNumofV(g) || findID <= 0)
                printf("Khong ton tai so hieu diem!\n"
                       "ID nam trong khoang 1 ---> %d\n",
                       getNumofV(g));
            else
                printf("Ten cua dia diem %d la: %s\n", findID, getVertex(g, findID));
        }
        break;

        case 2:
        {
            char busPlaceName1[100], busPlaceName2[100];
            printf("Nhap dia diem thu 1: ");
            rewind(stdin);
            gets(busPlaceName1);
            printf("Nhap dia diem thu 2: ");
            rewind(stdin);
            gets(busPlaceName2);
            int hasEdgeBus = hasEdge(g, busPlaceName1, busPlaceName2);
            if (hasEdgeBus == 0)
                printf("\nHai dia diem khong noi voi nhau!\n");
            else
                printf("\n%s noi truc tiep voi %s\n", busPlaceName1, busPlaceName2);
        }
        break;

        case 3:
        {
            printf("Nhap dia diem tim kiem: ");
            rewind(stdin);
            gets(findBusPlace);
            char *output[100];
            JRB busNameFind = jrb_find_str(g.vertices, findBusPlace);
            if (busNameFind == NULL)
                printf("Khong co dia diem trong ban do!\n");
            else
            {
                printf("\nCac dia diem noi truc tiep voi %s la: \n", findBusPlace);
                int directPlaceCnt = getAdjacentVertices(g, findBusPlace, output);
                for (int i = 0; i < directPlaceCnt; i++)
                {
                    printf("%s\n", output[i]);
                }
            }
        }
        break;

        case 4:
        {
            char *path[1000];
            char busPlaceName1[100], busPlaceName2[100];
            printf("Nhap dia diem thu 1: ");
            rewind(stdin);
            gets(busPlaceName1);
            printf("Nhap dia diem thu 2: ");
            rewind(stdin);
            gets(busPlaceName2);

            int pathNum = shortest_noWeight_path(g, busPlaceName1, busPlaceName2, path);

            printf("\n* Duong di ngan nhat giua %s va %s la: \n", busPlaceName1, busPlaceName2);

            for (int i = 0; i < pathNum; i++)
            {
                printf("%s", path[i]);
                if (i < pathNum - 1)
                    printf(" -> ");
            }

            printf("\n\n---- Lo Trinh ----\n");
            for (int i = 0; i < pathNum - 1; i++)
            {
                printf("%s ---> %s ", path[i], path[i + 1]);
                JRB find1 = jrb_find_str(g.vertices, path[i]);
                JRB find2 = jrb_find_str(g.vertices, path[i + 1]);

                JRB tree1 = (JRB)jval_v(find1->val);
                JRB tree2 = (JRB)jval_v(find2->val);

                printf("\nXe so ");
                jrb_traverse(node, tree1)
                {
                    if (jrb_find_str(tree2, jval_s(node->key)) != NULL)
                        printf("- %s ", jval_s(node->key));
                }
                printf("\n");
            }

            for (int i = 0; i < pathNum - 1; i++)
            {
            }
        }
        break;
        case 5:
        {
            printf("Nhap dia diem tim kiem: ");
            rewind(stdin);
            gets(findBusPlace);
            JRB busNameFind = jrb_find_str(g.vertices, findBusPlace);
            if (busNameFind == NULL)
                printf("Khong co dia diem trong ban do!\n");
            else
            {
                printf("Tat ca cac tuyen xe buyt di qua dia diem %s la: ", findBusPlace);
                JRB tree = (JRB)jval_v(busNameFind->val);
                jrb_traverse(node, tree)
                {
                    printf("%s\t", jval_s(node->key));
                }
                printf("\n");
            }
        }
        break;
        default:
            printf("Nhap lai gia tri!\n");
            break;
        }

    } while (selection != 0);

    dropGraph(g);
    return 0;
}

void inputDataFromTxt(Graph g, char filename[])
{
    IS is = new_inputstruct(filename);
    if (is == NULL)
    {
        printf("File fail!\n");
        exit(1);
    }

    char *busName;
    while (get_line(is) > 0)
    {
        if (strcmp(is->fields[0], "Tuyen") == 0)
        {
            busName = (char *)malloc(sizeof(char) * strlen(is->fields[3]) + 1);
            strcpy(busName, is->fields[3]);
            continue;
        }

        int busPlaceCnt = 0;
        for (int i = 0; i < is->NF; i++)
        {
            if (strcmp(is->fields[i], "-") == 0)
                busPlaceCnt++;
        }

        char *busPlaceName[++busPlaceCnt];
        int j = 0;
        busPlaceName[j] = (char *)malloc(sizeof(char) * 100);

        for (int i = 2; i < is->NF; i++)
        {
            if (strcmp(is->fields[i], "-") == 0)
            {
                j++;
                busPlaceName[j] = (char *)malloc(sizeof(char) * 100);
                continue;
            }
            else
            {
                strcat(busPlaceName[j], is->fields[i]);
                if (i < is->NF - 1)
                    if (strcmp(is->fields[i + 1], "-") != 0)
                        strcat(busPlaceName[j], " ");
            }
        }

        for (int i = 0; i < busPlaceCnt; i++)
            addVertex(g, busPlaceName[i], busName);

        for (int i = 0; i < busPlaceCnt - 1; i++)
            addEdge(g, busPlaceName[i], busPlaceName[i + 1]);
    }
}