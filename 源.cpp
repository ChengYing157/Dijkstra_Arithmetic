#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>//提供特殊函数
#include<stdlib.h>//提供文件操作类函数

#define NUMS 6   //节点个数
#define INF 65535//64位操作系统int最大值,用来表示无穷大

typedef struct
{
	char flag_vertex[NUMS];//判断节点是否被标记
	char front_vertex[NUMS];//前级节点
	int distance[NUMS];//权重
	int edges[NUMS][NUMS];//权重矩阵
	int n, e;//
}Graph;

Graph G;
char vertex_name[6] = { 's','a','b','c','d','e' };
FILE *fp1;
errno_t err1 = 0;

void Put_Path(Graph G);//节点1到各点的权重最小值
void ReadGraph(Graph *G);//读取路径
void Djikstra_Arithmetic(Graph G);//计算最短路径

int main()
{
	ReadGraph(&G);
	Djikstra_Arithmetic(G);
	
	return 0;
}

void ReadGraph(Graph *G)
{
	int i, j;
	if ((err1 = fopen_s(&fp1, "Dijkstra.txt", "r")) != 0)
	{
		printf("打开Dijkstra.txt文件失败!\n");
		system("pause");
		exit(0);
	}
	G->n = NUMS;
	G->e = NUMS * NUMS;
	for (i = 0; i < NUMS; i++)
	{
		for (j = 0; j < NUMS; j++)
		{
			fscanf_s(fp1, "%d", &(G->edges[i][j]));
		}
	}
	fclose(fp1);//关闭文件
}

void Djikstra_Arithmetic(Graph G)
{
	int i, j, k, tmp;

	for (i = 0; i < NUMS; i++)
	{
		G.distance[i] = INF;
		G.flag_vertex[i] = 0;//标记节点没有被确定
		G.front_vertex[i] = 0;
	}//初始化节点1到各点(包括自己)的距离无穷大

	G.distance[0] = 0;//初始化节点1到本节点总权重为0

	for (i = 0; i < NUMS; i++)
	{
		tmp = INF;

		for (j = 0; j < NUMS; j++)
		{
			if (G.flag_vertex[j] == 0 && G.distance[j] < tmp)
			{

				tmp = G.distance[j];
				k = j;
			}
		}//找出最小权值路径

		G.flag_vertex[k] = 1;

		for (j = 0; j < NUMS; j++)
		{
			if (G.edges[k][j] != 0 && G.flag_vertex[j] == 0 && G.distance[j] > G.distance[k] + G.edges[k][j])
			{
				G.distance[j] = G.distance[k] + G.edges[k][j];
				G.front_vertex[j] = k;
			}
		}
	}
	Put_Path(G);
}

void Put_Path(Graph G)
{
	int i;
	printf("顶点1与各点之间的最短路径分别为:\n");
	for (i = 1; i < NUMS; i++)
	{
		printf("%c <- ", vertex_name[i]);
		int tmp = G.front_vertex[i];
		while (tmp != 0)
		{
			printf("%c <- ", vertex_name[tmp]);
			tmp = G.front_vertex[tmp];
		}
		printf("s     权重: % d\r\n",G.distance[i]);
	}
	printf("\n");
}