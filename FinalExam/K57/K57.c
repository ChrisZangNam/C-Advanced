#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

void instruction();
void ReadFile(Graph graph, char *filename);
void xulichuoi(char str[], char code[], char name[]);
void xulichuoi2(char str[], char code1[], char code2[], double *weight);

int main()
{
    int choice;
    Graph graph = createGraph();
    char *code1, *code2;
    char name[20];

    instruction();
    printf("Nhap lua chon: ");
    scanf("%d%*c", &choice);

    while(choice != 0)
    {
        switch(choice)
        {
            case 1:
                ReadFile(graph, "input.txt");
                puts("Da hoan thanh doc file.");
                break;

            case 2:
                printf("So diem bay: %d\n", getNumOfV(graph));
                printf("So chuyen bay cua hang: %d\n", getNumOfE(graph));
                break;

            case 3:
                printf("Nhap ten mot tinh: ");
                rewind(stdin);
                gets(name);
                code1 = convertToCode(graph, name);
                // printf("%s\n", code1);

                printf("Cac tinh co chuyen bay den %s la: \n", name);
                JRB node;
                int total = 0;

                jrb_traverse(node, graph.vertices)
                {
                    if(hasEdge(graph, jval_s(node->key), code1))
                    {
                        printf("\t%s\n", jval_s(node->val));
                        total++;
                    }
                }

                if(total == 0)
                    printf("Khong co chuyen bay nao den %s\n", name);
                break;

            case 4:
                break;

            case 5:
                printf("Nhap ma hai tinh: \n");
                printf("\tTinh 1: ");
                rewind(stdin);
                gets(code1);
                printf("\tTinh 2: ");
                rewind(stdin);
                gets(code2);


                break;

            case 6:
                break;

            case 7:
                break;

            default:
                puts("Khong ton tai lua chon tren ! Vui long nhap lai !");
                break;
        }
        instruction();
        printf("Nhap lua chon: ");
        scanf("%d%*c", &choice);
    }
    puts("Ket thuc chuong trinh.");
}

void instruction()
{
    printf("----------MENU----------\n");
    puts("1. Doc File\n"
         "2. So luong diem bay, chuyen bay\n"
         "3. Cac chuyen bay thang den mot tinh\n"
         "4. In ra danh sach tinh co so duong bay nhieu nhat\n"
         "5. Kiem tra su ton tai hanh trinh bay giua hai tinh\n"
         "6. Thanh phan lien thong lien nhat voi mot tinh\n"
         "7. Lo trinh bay gia soc nhat giua 2 tinh\n"
         "0. Thoat chuong trinh\n");
}

void ReadFile(Graph graph, char *filename)
{
    FILE *f = fopen(filename, "r");
    if(f == NULL)
    {
        puts("Khong ton tai file.");
        exit(0);
    }
    char str[100], code[5], name[20];
    double weight;
    char code1[5], code2[5];

    while(!feof(f))
    {
        fscanf(f, "%[^\n]\n", str);
        if(strchr(str, '=') != NULL)
        {
            xulichuoi1(str, code, name);
            // printf("%s-%s\n", code, name);
            addVertex(graph, code, name);
        }
        else
        {
            xulichuoi2(str, code1, code2, &weight);
            // printf("%s-%s\n%lf\n", code1, code2, weight);
            addEdge(graph, code1, code2, weight);
        }
    }

}

void xulichuoi1(char str[], char code[], char name[])
{
    int i, j, k = 0;

    i = 0;
    while (str[i] != '=')
    {
        code[i] = str[i];
        i++;
    }

    code[i] = '\0';
    j = i + 2;
    for (j; j < strlen(str) - 1; j++)
        name[k++] = str[j];
    name[k] = '\0';
}

void xulichuoi2(char str[], char code1[], char code2[], double *weight)
{
    int i = 0, j = 0, k = 0;

    while (str[i] != ' ')
    {
        code1[i] = str[i];
        i++;
    }
    code1[i] = '\0';
    i++;
    while (str[i] != ' ')
    {
        code2[j] = str[i];
        i++;
        j++;
    }
    code2[j] = '\0';

    char wei[5];
    i++;
    while (str[i] != '\0')
    {
        wei[k] = str[i];
        i++;
        k++;
    }
    wei[k] = '\0';

    *weight = atof(wei);
}
