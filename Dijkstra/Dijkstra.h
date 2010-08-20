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
	int weight;//����Ȩֵ
}AdjMatrix[20][20];


typedef struct				//ͼ���ڽӾ�����ʽ����
{
	char vexs[20];
	AdjMatrix adjMatrixes;
	int vexNum,arcNum;
}AdjMGraph;

typedef struct ArcNode		//�����
{
	int adjvex;				//�ڽӵ���adjvex�����vi���ڽӵĶ���vj�����j
	struct ArcNode *next;	//���ڽӱ�����б�������һ��
}ArcNode;

typedef struct				//�ڽ����� ��ͷ���
{
	char vertex;			//������vertex��Ŷ���vi����Ϣ
	ArcNode *firstEdge;		//ָ���һ�������ý��Ļ���ָ��
}AdjList;


class Dijkstra
{
	private:

	public:
		int* data;
		Dijkstra();
		~Dijkstra();
		int CreatAdjMGraph_L(AdjMGraph &G,int* data,int dim);//����ͼ���ڽӾ����ʾ
		void ShortestPath(AdjMGraph gra,int n,int v);
		void BellmanFord(AdjMGraph gra,int n,int v); //�ڴ�Ȩ����ͼ���еı߾��и���Ȩֵ���Ӷ���v�ҵ�����������������·����
};

int Dijkstra::CreatAdjMGraph_L(AdjMGraph &G,int* data,int dim)//����ͼ���ڽӾ����ʾ
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
	/*G��һ������n������Ĵ�Ȩ����ͼ�������ϵ�Ȩֵ��Edge[i][j]���������㷨������һ�����飺
	dist[j],0<=j<n, �ǵ�ǰ�󵽵ĴӶ���v������j�����·�����ȣ�ͬʱ������path[j],0<=j<n,���
	�󵽵����·��
	*/
	for(int i=0;i<n;i++)//dist,path�����ʼ��
	{
		//�ڽӾ����v��Ԫ�ظ��Ƶ�dist��
		dist[i]=gra.adjMatrixes[v][i].weight;
		S[i]=false;							//��������·���Ķ��㼯�ϳ�ʼ��
		if(i!=v&&dist[i]<MAXNUM)
		{
			path[i]=v;
		}
		else
		{
			path[i]=-1;					//·����������ʼ��
		}
	}
	cout<<v<<" was selected into the shortest vertexes arrays"<<endl;
	S[v]=true;//����v���붥�㼯��
	dist[v]=0;//v��v�ľ���Ϊ0
	for(int i=0;i<n-1;i++)//�Ӷ���vȷ��n-1��·��
	{
		int min=MAXNUM;
		int u=v;
		for(int j=0;j<n;j++)//ѡ��ǰ���ڼ���S�о������·���Ķ���u
		{
			if(!S[j]&&dist[j]<min)
			{
				u=j;
				min=dist[j];
			}
		}
		cout<<u<<" was selected into the shortest vertexes arrays"<<endl;
		S[u]=true;//������S���뼯��S����ʾ���������·����
		for(int w=0;w<n;w++)//�޸���u���ڵ�w�������̾���
		{
			if(!S[w]&&gra.adjMatrixes[u][w].weight<MAXNUM&&dist[u]+gra.adjMatrixes[u][w].weight<dist[w])//w���㲻�����·���Ķ��㼯��&&u,w����&&��u��w�ľ���С�ڵ�ǰw�����·��
			{
				dist[w]=dist[u]+gra.adjMatrixes[u][w].weight;//�޸�w����̾���
				cout<<"now changing the "<<w<<"'s dist to "<<dist[w]<<endl;
				cout<<"now changing the "<<w<<"'s neighbor vertex to be "<<u<<endl;
				path[w]=u;//�޸�w�����·��
			}
		}
	}
}

/*����ȨֵΪ����ֵ�ĵ�Դ���·������,���㷨����ShortestPath�Ĳ���*/
void Dijkstra::BellmanFord(AdjMGraph gra,int n,int v) //�ڴ�Ȩ����ͼ���еı߾��и���Ȩֵ���Ӷ���v�ҵ�����������������·����
{
	for(int i=0;i<n;i++)
	{
		//��dist��ʼ��
		dist[i]=gra.adjMatrixes[v][i].weight;
		//��path��ʼ��
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
						path[u]=i;		//��i��·������С���޸�
					}
				}
			}
		}
	}
}
