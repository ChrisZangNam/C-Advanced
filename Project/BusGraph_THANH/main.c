#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "jrb.h"
#include "dllist.h"

#define INFINITIVE_VALUE  10000000

typedef struct {
    JRB edges; //cạnh
    JRB vertices; //đỉnh
} Graph;

typedef struct{
    JRB ten_tuyen;
    int weight;

} data;

int so_ben = 0;

Graph createGraph();
void addVertex(Graph g, char *key, int val);
int getVertex(Graph graph, char *key);
void addEdge(Graph graph, char *v1, char *v2, char *cur_tuyen);
int getEdgeValue(Graph graph, char *v1, char *v2, char *cur_tuyen);
int indegree(Graph graph, int v, int* output);
int outdegree (Graph graph, char *v, int* output);
void getName(Graph g, int val, char *name);
double shortestPath(Graph g, char *start, char *target, int* path, int*length);
void dropGraph(Graph graph);
void DocFile(FILE *f, Graph graph);
void display_dinh(Graph g);
void display_canh(Graph g);



int main()
{
    //  int i, length, path[100], s, t;
	//  double w;
	//  Graph g = createGraph();
	//  addVertex(g, 0, "V0");
	//  addVertex(g, 1, "V1");
	//  addVertex(g, 2, "V2");
	//  addVertex(g, 3, "V3");
	//  addEdge(g, 0, 1, 1);
	//  addEdge(g, 1, 2, 3);
	//  addEdge(g, 2, 0, 3);
	//  addEdge(g, 1, 3, 1);
	//  addEdge(g, 3, 2, 1);
	//  s = 0;
	//  t = 2;
	//  w = shortestPath(g, s, t, path, &length);
	//  if (w == INFINITIVE_VALUE)
	//  {
	//       printf("No path from %s to %s\n", getVertex(g, s), getVertex(g, t));
	//  }else
	//  {
	//       printf("Path from %s to %s (with total distance %f)\n", getVertex(g, s), getVertex(g, t), w);
	//       for (i=0; i<length; i++)
	//           printf(" => %s", getVertex(g, path[i]));
	//  }
	FILE *f;
	Graph g = createGraph();
	char start[50] = "Ben xe Gia Lam ";
	char target[50] = "Thuy Loi ";
	char ten_ben[50];
	int i, length, path[100], s, t;
	double w;
	f = fopen("input1.txt","r");
	DocFile(f,g);
	display_dinh(g);
	printf("\n\n\n\n");
	//display_canh(g);
	w = shortestPath(g, start, target, path, &length);
	if (w == INFINITIVE_VALUE)
    {
        printf("No path from %s to %s\n", start, target);
    }
    else
    {
        printf("Path from %s to %s (with total distance %f)\n", start, target, w);
        for (i = 0; i < length; i++)
        {
            getName(g, path[i], ten_ben);
            printf(" => %s", ten_ben);
        }
    }
	fclose(f);
	//dropGraph(g);
}

Graph createGraph()
{
	Graph g;
	g.edges = make_jrb();
	g.vertices = make_jrb();
	return g;
}

void addVertex(Graph g, char *key, int val)
{
	JRB node = jrb_find_str(g.vertices, strdup(key));
	if (node==NULL) // only add new vertex
		jrb_insert_str(g.vertices, strdup(key), new_jval_i(val));
}

int getVertex(Graph g, char *key) //lay dinh
{
	JRB node = jrb_find_str(g.vertices, strdup(key)); //tim dinh trong graph
	if (node == NULL)
		return -9999;
	else
		return jval_i(node->val); //return so ung voi key
}

void addEdge(Graph graph, char *v1, char *v2, char *cur_tuyen)//ham then chot 2
{
	JRB node, node_find_v2, tree;
	if (getEdgeValue(graph, v1, v2, cur_tuyen) == 0)
	{
		node = jrb_find_str(graph.edges, strdup(v1));//tim xem v1 co chua
		if (node==NULL) {//chua co thi tao cay moi, luc nay v2 chac chan chua co trong cay cua v1 => gan value moi toanh cho v2
			tree = make_jrb();
			jrb_insert_str(graph.edges, strdup(v1), new_jval_v(tree));
			data *p;
			p = malloc(sizeof(data));
			p->weight = 1;
			p->ten_tuyen = make_jrb();
			jrb_insert_str(p->ten_tuyen, strdup(cur_tuyen), new_jval_s(strdup(cur_tuyen)));
			jrb_insert_str(tree, strdup(v2), new_jval_v((void*)p));
		} else//co roi thi gan cay con vao bien tree
		{
			tree = (JRB) jval_v(node->val);
			node_find_v2 = jrb_find_str(tree, strdup(v2));
			if (node_find_v2 == NULL)//v2 chua co trong cay con cua v1 => gan value moi toanh cho v2
			{
			    data *p;
                p = malloc(sizeof(data));
                p->weight = 1;
                p->ten_tuyen = make_jrb();
                jrb_insert_str(p->ten_tuyen, strdup(cur_tuyen), new_jval_s(strdup(cur_tuyen)));
                jrb_insert_str(tree, strdup(v2), new_jval_v((void*)p));
			}
			else //v2 co nhung trong value cua v2 chua co ten_tuyen dinh truyen
            {
                data *val_of_v2;
                val_of_v2 = malloc(sizeof(data));
                val_of_v2 = (data*) node_find_v2->val.v; //gan value cua v2 vao val_of_v2
                jrb_insert_str(val_of_v2->ten_tuyen, strdup(cur_tuyen), new_jval_s(strdup(cur_tuyen)));
            }
		}
	}
}

int getEdgeValue(Graph graph, char *v1, char *v2, char *cur_tuyen)//ham then chot 1
{
	JRB node, tree;
	node = jrb_find_str(graph.edges, strdup(v1));
	if (node==NULL)
		return 0;
	tree = (JRB) jval_v(node->val);
	node = jrb_find_str(tree, strdup(v2));
	if (node==NULL)
		return 0;
	if(node != NULL) //da co v2, tim xem ten_tuyen da co trong data->ten_tuyen chua?
    {
        data *p;
        p = malloc(sizeof(data));
        p = (data*) node->val.v;
        JRB tmp;
        tmp = jrb_find_str(p->ten_tuyen, strdup(cur_tuyen));
        if(tmp == NULL)
            return 0;
    }
    return 1;
}

int indegree (Graph graph, int v, int* output)//ham nay khong dung den
{
	JRB tree, node;
	int total = 0;
	jrb_traverse(node, graph.edges)
	{
		tree = (JRB) jval_v(node->val);
		if (jrb_find_int(tree, v))
		{
			output[total] = jval_i(node->key);
			total++;
		}
	}
	return total;
}

void dropGraph(Graph graph)
{
	JRB node, tree;
	jrb_traverse(node, graph.edges)
	{
		tree = (JRB) jval_v(node->val);
		jrb_free_tree(tree);
	}
	jrb_free_tree(graph.edges);
	jrb_free_tree(graph.vertices);
}

void DocFile(FILE *f, Graph g)
{
    data *p;
    p = malloc(sizeof(data));
	f = fopen("input1.txt", "r");
	char tmp[100];
	fgets(tmp, 100, f);
	char ten_ben_1[100];
	ten_ben_1[0] = '\0';
	char ten_tuyen[100];
	char ten_ben_2[100];
	ten_ben_2[0] = '\0';
	while(tmp[0] != '?')
	{
		fscanf(f, "%s", ten_tuyen);
		fscanf(f, "%s", tmp);//doc dau 2 cham
		fscanf(f, "%s", tmp);//doc cum dau tien cua ten ben
		while(1)
		{
			while(tmp[0] != '-' && tmp[0] != '.' && tmp[0] != '?')
			{
				strcat(ten_ben_1, tmp);
				strcat(ten_ben_1, " ");
				fscanf(f, "%s", tmp);

			}
            if( jrb_find_str(g.vertices, strdup(ten_ben_1)) == NULL)
            {
                addVertex(g, strdup(ten_ben_1), so_ben++);
            }

			tmp[0] = '\0';
			fscanf(f, "%s", tmp);
			while(tmp[0] != '-' && tmp[0] != '.' && tmp[0] != '?')
			{
				strcat(ten_ben_2, tmp);
				strcat(ten_ben_2, " ");
				fscanf(f, "%s", tmp);
			}
            if( jrb_find_str(g.vertices, strdup(ten_ben_2)) == NULL)
            {
                addVertex(g, strdup(ten_ben_2), so_ben++);
            }
			addEdge(g, ten_ben_1, ten_ben_2, ten_tuyen);
			if (tmp[0] == '.' || tmp[0] == '?')
			{
			    ten_tuyen[0] = '\0';
			    ten_ben_1[0] = '\0';
			    ten_ben_2[0] = '\0';
				break;
			}else
			{
				fseek(f, -((strlen(ten_ben_2) -1) + 2), SEEK_CUR);//vi luc nay ten_ben_2 co dau ' ' o cuoi
				fscanf(f, "%s", tmp);
			}
			ten_ben_1[0] = '\0';
			ten_ben_2[0] = '\0';
		}
	}
}

double shortestPath(Graph g, char *start, char *target, int* path, int*length) //length luu so buoc
{
   double distance[1000], min, w, total; //total la chi phi di tu s den t. w la trong so.
   int previous[1000], tmp[1000]; //previous de luu
   int n, output[100], i, u, v;
   Dllist ptr, queue, node;
   int s = getVertex(g, strdup(start));
   int t = getVertex(g, strdup(target));

   for (i=0; i<1000; i++)
       distance[i] = INFINITIVE_VALUE;
   distance[s] = 0;
   previous[s] = s;

   queue = new_dllist();
   dll_append(queue, new_jval_i(s));

   while ( !dll_empty(queue) )
   {
      // get u from the priority queue
      min = INFINITIVE_VALUE;
      dll_traverse(ptr, queue)//hang doi luu cac dinh ke tu 1 dinh U dang xet, khi ket thuc 1 lan lap
      //trong vong lap thi cac dinh ke voi dinh U se duoc them vao queue, moi khi duyet queue thi dinh co distance nho nhat se bi
      //xoa khoi queue
      {
          u = jval_i(ptr->val);
          if (min > distance[u])
          {
             min = distance[u];
             node = ptr;
          }
      }
      dll_delete_node(node);//moi them vao hang doi o tren roi xoa luon

      if (u == t) break; // stop at target
      char name[50];
      getName(g, u, name);
      n = outdegree(g, name, output);//xuat ra so luong dinh u tro den va luu cac dinh do vao output
      for (i = 0; i < n; i++)//duyet cac dinh ke
      {
          v = output[i];
          //w = getEdgeValue(g, u, v);
          w = 1;
          if ( distance[v] > distance[u] + w )
          {
              distance[v] = distance[u] + w;
              previous[v] = u;
          }
          dll_append(queue, new_jval_i( v ));//them cac dinh ke vao queue
      }
   }
   total = distance[t];
   if (total != INFINITIVE_VALUE)
   {
       tmp[0] = t;//luu tmp[0] la target
       n = 1;
       while (t != s)//luu duong di nguoc tu target len start
       {
             t = previous[t];
             tmp[n++] = t;
       }
       for (i=n-1; i>=0; i--)//luu duong tu start den target vao path[]
           path[n-i-1] = tmp[i];
       *length = n;
   }
   return total;
}

void getName(Graph g, int val, char *name) //truyen vao so, luu ten ung vs so vao bien name
{
    JRB node, tree;
    jrb_traverse(node, g.vertices) //duyet do thi g.dinh
    {
        char hehe[50];
        strcpy(hehe, jval_s(node->key));
        if( getVertex(g, jval_s(node->key)) == val)//so sanh value cua dinh va val truyen vao, neu bang nhau => val la value cua dinh
            {
                strcpy(name, jval_s(node->key)); //luu ten dinh vao name
                return;
            }
    }
    return;
}

int outdegree (Graph graph, char *v, int* output) //dua vao dinh v, return so dinh ke vs dinh v va luu vao ham output duoi dang int
{
    JRB tree, node;
	int total;
	node = jrb_find_str(graph.edges, strdup(v));
	if (node==NULL)
		return 0;
	tree = (JRB) jval_v(node->val);
	total = 0;
	jrb_traverse(node, tree)
	{
		output[total] = getVertex(graph, jval_s(node->key));
		total++;
	}
	return total;
}


void display_dinh(Graph g)
{
    JRB node;
    node = make_jrb();
    jrb_traverse(node, g.vertices)
    {
        printf("%s\n%d\n", node->key, node->val);
    }
}


void display_canh(Graph g)
{
    JRB dinh_ke, cay_dinh_ke, tmp, cay_luu_tuyen, dinh_tuyen;
    cay_luu_tuyen = make_jrb();

    char tenBen[50] = "Ben xe Gia Lam ";//nho ten ben cua chung ta co dau cach o cuoi ;)
    tmp = jrb_find_str(g.edges, strdup(tenBen));
    if (tmp == NULL)
        return;
    cay_dinh_ke = (JRB) jval_v(tmp->val);//tree gio la cay con cua Ben xe Gia Lam
    printf("\nBen xe Gia Lam: ");
        //duyet cay dinh ke
        jrb_traverse(dinh_ke, cay_dinh_ke)
        {
            printf("\n%s: ",jval_s(dinh_ke->key));
            data *p;
            p = malloc(sizeof(data));
            p->weight = 0;
            p->ten_tuyen = make_jrb();
            p = (data*) dinh_ke->val.v;
            printf("%d - ", p->weight);
            cay_luu_tuyen = p->ten_tuyen;//ky la la ro rang p->ten-tuyen la cay ma gan the nay lai sai :(( "cay_luu_tuyen = (JRB) jval_v(p->ten_tuyen);"
             //duyet cay luu tuyen
            jrb_traverse(dinh_tuyen, cay_luu_tuyen)
            {
                printf("%s, ",jval_s(dinh_tuyen->key));
            }
       }
}
