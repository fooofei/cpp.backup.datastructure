#include "Graph.h"
int main()
{
	Graph G;
	CreateGraph(&G);
	MiniSpanTree_Kruskal(&G);
	return 0;
}