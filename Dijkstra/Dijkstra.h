// Dijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stack.h"
#include <stdio.h>
#include<iostream>
using namespace std;

#define MAXVERTEX 20
#define MAXNUM 9999
int dist[MAXVERTEX];
bool S[MAXVERTEX];
int path[MAXVERTEX];

typedef struct
{
	int weight;//弧的权值
}AdjMatrix[20][20];


typedef struct				//图的邻接矩阵形式定义
{
	char vexs[20];
	AdjMatrix adjMatrixes;
	int vexNum,arcNum;
}AdjMGraph;

typedef struct ArcNode		//弧结点
{
	int adjvex;				//邻接点域adjvex存放与vi相邻接的顶点vj的序号j
	struct ArcNode *next;	//将邻接表的所有表结点链在一起。
}ArcNode;

typedef struct				//邻接链表 表头结点
{
	char vertex;			//顶点域vertex存放顶点vi的信息
	ArcNode *firstEdge;		//指向第一条依附该结点的弧的指针
}AdjList;


class Dijkstra
{
	private:

	public:
		int* data;
		Dijkstra();
		~Dijkstra();
		int CreatAdjMGraph_L(AdjMGraph &G,int* data,int dim);//创建图用邻接矩阵表示
		void ShortestPath(AdjMGraph gra,int n,int v);
		void BellmanFord(AdjMGraph gra,int n,int v); //在带权有向图中有的边具有负的权值。从顶点v找到所有其它顶点的最短路径。
};

int Dijkstra::CreatAdjMGraph_L(AdjMGraph &G,int* data,int dim)//创建图用邻接矩阵表示
{
	G.vexNum=7;
	G.arcNum=9;
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j!=G.vexNum;++j)
		{ 
			G.adjMatrixes[i][j].weight=MAXNUM;
		}
			
		_itoa_s( i, &G.vexs[i],8,10);

		for(int j=0;j<dim;j++)
		{
			if(data[dim*i+j]<MAXNUM)
			{
				G.adjMatrixes[i][j].weight=data[dim*i+j];
				G.adjMatrixes[j][i].weight=data[dim*i+j];
			}
		}
	}
	return G.vexNum;
}

void Dijkstra::ShortestPath(AdjMGraph gra,int n,int v)
{
	/*G是一个具有n个顶点的带权有向图，各边上的权值由Edge[i][j]给出。本算法建立起一个数组：
	dist[j],0<=j<n, 是当前求到的从顶点v到顶点j的最短路径长度，同时用数组path[j],0<=j<n,存放
	求到的最短路径
	*/
	for(int i=0;i<n;i++)//dist,path数组初始化
	{
		//邻接矩阵第v行元素复制到dist中
		dist[i]=gra.adjMatrixes[v][i].weight;
		S[i]=false;							//已求出最短路径的顶点集合初始化
		if(i!=v&&dist[i]<MAXNUM)
		{
			path[i]=v;
		}
		else
		{
			path[i]=-1;					//路径存放数组初始化
		}
	}
	cout<<v<<" was selected into the shortest vertexes arrays"<<endl;
	S[v]=true;//顶点v加入顶点集合
	dist[v]=0;//v到v的距离为0
	for(int i=0;i<n-1;i++)//从顶点v确定n-1条路径
	{
		int min=MAXNUM;
		int u=v;
		for(int j=0;j<n;j++)//选择当前不在集合S中具有最短路径的顶点u
		{
			if(!S[j]&&dist[j]<min)
			{
				u=j;
				min=dist[j];
			}
		}
		cout<<u<<" was selected into the shortest vertexes arrays"<<endl;
		S[u]=true;//将顶点S加入集合S，表示它已在最短路径上
		for(int w=0;w<n;w++)//修改与u相邻的w顶点的最短距离
		{
			if(!S[w]&&gra.adjMatrixes[u][w].weight<MAXNUM&&dist[u]+gra.adjMatrixes[u][w].weight<dist[w])//w顶点不在最短路径的顶点集合&&u,w相邻&&经u到w的距离小于当前w的最短路径
			{
				dist[w]=dist[u]+gra.adjMatrixes[u][w].weight;//修改w的最短距离
				cout<<"now changing the "<<w<<"'s dist to "<<dist[w]<<endl;
				cout<<"now changing the "<<w<<"'s neighbor vertex to be "<<u<<endl;
				path[w]=u;//修改w的最短路径
			}
		}
	}
}

/*边上权值为任意值的单源最短路径问题,此算法补足ShortestPath的不足*/
void Dijkstra::BellmanFord(AdjMGraph gra,int n,int v) //在带权有向图中有的边具有负的权值。从顶点v找到所有其它顶点的最短路径。
{
	for(int i=0;i<n;i++)
	{
		//对dist初始化
		dist[i]=gra.adjMatrixes[v][i].weight;
		//对path初始化
		if(i!=v&&dist[i]<MAXNUM)
			path[i]=v;
		else
			path[i]=-1;
	}
	for(int k=2;k<n;k++)
	{
		for(int u=0;u<n;u++)
		{
			if(u!=v)
			{
				for(int i=0;i<n;i++)
				{
					if(gra.adjMatrixes[i][u].weight>0&&gra.adjMatrixes[i][u].weight<MAXNUM&&dist[u]>dist[i]+gra.adjMatrixes[i][u].weight)
					{
						dist[u]=dist[i]+gra.adjMatrixes[i][u].weight;
						path[u]=i;		//绕i的路径长度小，修改
					}
				}
			}
		}
	}
}
