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
	
	AdjMGraph G;
	int data[7][7]={{MAXNUM,28,MAXNUM,MAXNUM,MAXNUM,10,MAXNUM},
					{28,MAXNUM,16,MAXNUM,MAXNUM,MAXNUM,14},
					{MAXNUM,16,MAXNUM,12,MAXNUM,MAXNUM,MAXNUM},
					{MAXNUM,MAXNUM,12,MAXNUM,22,MAXNUM,18},
					{MAXNUM,MAXNUM,MAXNUM,22,MAXNUM,25,24},
					{10,MAXNUM,MAXNUM,MAXNUM,25,MAXNUM,MAXNUM},
					{MAXNUM,14,MAXNUM,18,24,MAXNUM,MAXNUM}};
	Dijkstra *dij=new Dijkstra(*data,7);
	dij->ShortestPath(7,0);
	dij->PrintPath();

	return 0;
}

