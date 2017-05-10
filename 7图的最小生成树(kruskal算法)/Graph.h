#ifndef GRAPH_H
#define GRAPH_H
#define INFINITY 65535
#define MAXVEX 20
#define MAXEDGE 20
typedef char VertexType; //�������������
typedef int EdgeType; //�ߵ�Ȩֵ����
typedef struct graph{
	VertexType Vertex[MAXVEX]; //ͼ�Ķ���
	EdgeType Edge[MAXVEX][MAXEDGE]; //ͼ�ı߼�
	int NumVertex,NumEdge; //ͼ�Ķ������ͱ���
}Graph;
typedef struct edge{
	int begin;
	int end;
	int weight;
}Edge;
void CreateGraph(Graph *G);
void MiniSpanTree_Kruskal(Graph *G);
void sort(Edge *e,Graph *G);
void swap(Edge *e,int i,int j);
int Find(int *parent,int f);
#endif //GRAPH_H