#ifndef GRAPH_H
#define GRAPH_H
#define INFINITY 65535
#define MAXVEX 20
#define MAXEDGE 20
typedef char VertexType; //顶点的数据类型
typedef int EdgeType; //边的权值类型
typedef struct graph{
	VertexType Vertex[MAXVEX]; //图的顶点
	EdgeType Edge[MAXVEX][MAXEDGE]; //图的边集
	int NumVertex,NumEdge; //图的顶点数和边数
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