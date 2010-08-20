// Dijkstra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "stack.h"
#include "Dijkstra.h"
#include <stdio.h>
#include<iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int preVertex;
	int nextVertex;
	AdjMGraph_L G;
	int data[7][7]={{MAXNUM,28,MAXNUM,MAXNUM,MAXNUM,10,MAXNUM},
					{28,MAXNUM,16,MAXNUM,MAXNUM,MAXNUM,14},
					{MAXNUM,16,MAXNUM,12,MAXNUM,MAXNUM,MAXNUM},
					{MAXNUM,MAXNUM,12,MAXNUM,22,MAXNUM,18},
					{MAXNUM,MAXNUM,MAXNUM,22,MAXNUM,25,24},
					{10,MAXNUM,MAXNUM,MAXNUM,25,MAXNUM,MAXNUM},
					{MAXNUM,14,MAXNUM,18,24,MAXNUM,MAXNUM}};
	CreatAdjMGraph_L(G,*data,7);//创建图用邻接矩阵表示
	ShortestPath(G,7,0);
	for(int i=0;i<7;i++)
	{
		preVertex=i;
		SeqStack *S=new SeqStack();
		InitStack(S);
	
		cout<<i<<":";
		if(preVertex>=0)
		{
			Push(S,preVertex);
		}
		preVertex=path[preVertex];
		while(preVertex>=0)
		{	
			Push(S,preVertex);
			preVertex=path[preVertex];
		}
		
		while(!StackEmpty(S))
		{
			cout<<Pop(S)<<",";
		}
		cout<<"->"<<dist[i]<<endl;
	}
	return 0;
}

