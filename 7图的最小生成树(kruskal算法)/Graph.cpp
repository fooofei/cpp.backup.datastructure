#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
void CreateGraph(Graph *G)
{
	G->NumVertex = 7;
	G->NumEdge = 12;
	G->Vertex[0] = 'a';  //���������
	G->Vertex[1] = 'b';
	G->Vertex[2] = 'c';
	G->Vertex[3] = 'd';
	G->Vertex[4] = 'e';
	G->Vertex[5] = 'f';
	G->Vertex[6] = 'g';
	for(int i = 0;i < G->NumVertex;++i) //��ʼ��ͼ�ı߼�
		for(int j = 0;j < G->NumEdge;++j)
		{
			if(i == j) //�������Լ������Լ��Ķ���
				G->Edge[i][j] = 0;
			else
				G->Edge[i][j] = INFINITY;
		}
	G->Edge[0][1] = 2;  //�߱��Ȩֵ
	G->Edge[0][2] = 4;
	G->Edge[0][3] = 1;
	G->Edge[1][3] = 3;
	G->Edge[1][4] = 10;
	G->Edge[2][3] = 2;
	G->Edge[2][5] = 5;
	G->Edge[3][4] = 7;
	G->Edge[3][5] = 8;
	G->Edge[3][6] = 4;
	G->Edge[4][6] = 6;
	G->Edge[5][6] = 1;
	//��Ϊ������ͼ���Դ��ڷ��������
	for(int i = 0;i < G->NumVertex;++i)
		for(int j = i;j < G->NumVertex;++j)
			G->Edge[j][i] = G->Edge[i][j];
}
void MiniSpanTree_Kruskal(Graph *G)
{
	Edge edge[MAXVEX]; //�������õı߼�
	int parent[MAXVEX]; //�洢��ʹ�õĶ����±� ,��ֹ���ֻ�·
	int n = 0,m = 0,k = 0;
	for(int i = 0;i < MAXVEX;++i)
		parent[i] = 0;
	for(int i = 0;i < G->NumVertex - 1;++i)
		for(int j = i + 1;j < G->NumVertex;++j)
		{
			if(G->Edge[i][j] < INFINITY)
			{
				edge[k].weight = G->Edge[i][j];
				edge[k].begin = i;
				edge[k].end = j;
				++k;
			}
		}
	sort(edge,G);
	for(int i = 0;i < G->NumEdge;++i)
	{
		n = Find(parent,edge[i].begin);
		m = Find(parent,edge[i].end);
		if(n != m)
		{
			parent[n] = m;
			printf("(%d,%d) %d",edge[i].begin,edge[i].end,edge[i].weight);
		}
	}
}
void sort(Edge *e,Graph *G)
{
	for(int i = 0;i < G->NumEdge - 1;++i)
	{
		for(int j = i + 1;j < G->NumEdge;++j)
		{
			if(e[j].weight < e[i].weight)
				swap(e,i,j);
		}
	}
	for(int i = 0;i < G->NumEdge;++i)
	{
		printf("(%d,%d) %d\t",e[i].begin,e[i].end,e[i].weight);
		printf("\n");
	}
}
void swap(Edge *e,int i,int j)
{
	int temp;
	temp = e[i].begin;
	e[i].begin = e[j].begin;
	e[j].begin = temp;
	temp = e[i].end;
	e[i].end = e[j].end;
	e[j].end = temp;
	temp = e[i].weight;
	e[i].weight = e[j].weight;
	e[j].weight = temp;
}
int Find(int *parent,int f)
{
	while(parent[f] > 0)
		f = parent[f];
	return f;
}