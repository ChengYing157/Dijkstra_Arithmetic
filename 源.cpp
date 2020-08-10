#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>//�ṩ���⺯��
#include<stdlib.h>//�ṩ�ļ������ຯ��

#define NUMS 6   //�ڵ����
#define INF 65535//64λ����ϵͳint���ֵ,������ʾ�����

typedef struct
{
	char flag_vertex[NUMS];//�жϽڵ��Ƿ񱻱��
	char front_vertex[NUMS];//ǰ���ڵ�
	int distance[NUMS];//Ȩ��
	int edges[NUMS][NUMS];//Ȩ�ؾ���
	int n, e;//
}Graph;

Graph G;
char vertex_name[6] = { 's','a','b','c','d','e' };
FILE *fp1;
errno_t err1 = 0;

void Put_Path(Graph G);//�ڵ�1�������Ȩ����Сֵ
void ReadGraph(Graph *G);//��ȡ·��
void Djikstra_Arithmetic(Graph G);//�������·��

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
		printf("��Dijkstra.txt�ļ�ʧ��!\n");
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
	fclose(fp1);//�ر��ļ�
}

void Djikstra_Arithmetic(Graph G)
{
	int i, j, k, tmp;

	for (i = 0; i < NUMS; i++)
	{
		G.distance[i] = INF;
		G.flag_vertex[i] = 0;//��ǽڵ�û�б�ȷ��
		G.front_vertex[i] = 0;
	}//��ʼ���ڵ�1������(�����Լ�)�ľ��������

	G.distance[0] = 0;//��ʼ���ڵ�1�����ڵ���Ȩ��Ϊ0

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
		}//�ҳ���СȨֵ·��

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
	printf("����1�����֮������·���ֱ�Ϊ:\n");
	for (i = 1; i < NUMS; i++)
	{
		printf("%c <- ", vertex_name[i]);
		int tmp = G.front_vertex[i];
		while (tmp != 0)
		{
			printf("%c <- ", vertex_name[tmp]);
			tmp = G.front_vertex[tmp];
		}
		printf("s     Ȩ��: % d\r\n",G.distance[i]);
	}
	printf("\n");
}