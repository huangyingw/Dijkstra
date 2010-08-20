// Dijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\..\stack\stack\stack.h"
#include <stdio.h>
#include<iostream>
#include <fstream>
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
		ofstream fout;
		 
	public:
		int* data;
		AdjMGraph amg;
		Dijkstra(int* data,int dim);//����ͼ���ڽӾ����ʾ
		~Dijkstra();
		void ShortestPath(int n,int v);
		void PrintPath();
		void BellmanFord(int n,int v); //�ڴ�Ȩ����ͼ���еı߾��и���Ȩֵ���Ӷ���v�ҵ�����������������·����
};

Dijkstra::~Dijkstra()
{
		fout.close();
}

void Dijkstra::PrintPath()
{
	int preVertex;
	for(int i=0;i<7;i++)
	{
		preVertex=i;
		SeqStack<int> *S=new SeqStack<int>();
		S->InitStack();
	
		fout<<i<<":";
		if(preVertex>=0)
		{
			S->Push(preVertex);
		}
		preVertex=path[preVertex];
		while(preVertex>=0)
		{	
			S->Push(preVertex);
			preVertex=path[preVertex];
		}
		
		while(!S->StackEmpty())
		{
			fout<<S->Pop()<<",";
		}
		fout<<"->"<<dist[i]<<endl;
	}
}

Dijkstra::Dijkstra(int* data,int dim)//����ͼ���ڽӾ����ʾ
{
	fout.open("output.txt");
	amg.vexNum=7;
	amg.arcNum=9;
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j!=amg.vexNum;++j)
		{ 
			amg.adjMatrixes[i][j].weight=MAXNUM;
		}
			
		_itoa_s( i, &amg.vexs[i],8,10);

		for(int j=0;j<dim;j++)
		{
			if(data[dim*i+j]<MAXNUM)
			{
				amg.adjMatrixes[i][j].weight=data[dim*i+j];
				amg.adjMatrixes[j][i].weight=data[dim*i+j];
			}
		}
	}
}

void Dijkstra::ShortestPath(int n,int v)
{
	/*G��һ������n������Ĵ�Ȩ����ͼ�������ϵ�Ȩֵ��Edge[i][j]���������㷨������һ�����飺
	dist[j],0<=j<n, �ǵ�ǰ�󵽵ĴӶ���v������j�����·�����ȣ�ͬʱ������path[j],0<=j<n,���
	�󵽵����·��
	*/
	for(int i=0;i<n;i++)//dist,path�����ʼ��
	{
		//�ڽӾ����v��Ԫ�ظ��Ƶ�dist��
		dist[i]=amg.adjMatrixes[v][i].weight;
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
	fout<<v<<" was selected into the shortest vertexes arrays"<<endl;
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
		fout<<u<<" was selected into the shortest vertexes arrays"<<endl;
		S[u]=true;//������S���뼯��S����ʾ���������·����
		for(int w=0;w<n;w++)//�޸���u���ڵ�w�������̾���
		{
			if(!S[w]&&amg.adjMatrixes[u][w].weight<MAXNUM&&dist[u]+amg.adjMatrixes[u][w].weight<dist[w])//w���㲻�����·���Ķ��㼯��&&u,w����&&��u��w�ľ���С�ڵ�ǰw�����·��
			{
				dist[w]=dist[u]+amg.adjMatrixes[u][w].weight;//�޸�w����̾���
				fout<<"now changing the "<<w<<"'s dist to "<<dist[w]<<endl;
				fout<<"now changing the "<<w<<"'s neighbor vertex to be "<<u<<endl;
				path[w]=u;//�޸�w�����·��
			}
		}
	}
}

/*����ȨֵΪ����ֵ�ĵ�Դ���·������,���㷨����ShortestPath�Ĳ���*/
void Dijkstra::BellmanFord(int n,int v) //�ڴ�Ȩ����ͼ���еı߾��и���Ȩֵ���Ӷ���v�ҵ�����������������·����
{
	for(int i=0;i<n;i++)
	{
		//��dist��ʼ��
		dist[i]=amg.adjMatrixes[v][i].weight;
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
					if(amg.adjMatrixes[i][u].weight>0&&amg.adjMatrixes[i][u].weight<MAXNUM&&dist[u]>dist[i]+amg.adjMatrixes[i][u].weight)
					{
						dist[u]=dist[i]+amg.adjMatrixes[i][u].weight;
						path[u]=i;		//��i��·������С���޸�
					}
				}
			}
		}
	}
}
