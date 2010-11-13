#include<iostream>
using namespace std;

#define StackSize 10 //假定预分配的栈空间最多为100个元素
//typedef char DataType;//假定栈元素的数据类型为字符
typedef struct
{
	int data[StackSize];//注意，此处限定了数组的长度
    int top;
}SeqStack;

int Pop(SeqStack *S);

void Error(char* message)
{
	cout<<message<<endl;
}

//置栈空
void InitStack(SeqStack *S)
{	//将顺序栈置空
	S->top=-1;
} 

//判栈空
int StackEmpty(SeqStack *S)
{
	return S->top==-1;
} 

//判栈满
int StackFull(SeqStack *S)
{
	return S->top==StackSize-1;
} 

//进栈
void Push(SeqStack *S,int x)
{
	if(StackFull(S))
	{
		Error("Stack overflow"); //上溢，退出运行
		cout<<Pop(S)<<endl;
	}
	S->data[++S->top]=x;//栈顶指针加1后将x入栈
}

//退栈
int Pop(SeqStack *S)
{
	if(StackEmpty(S))
		Error("Stack underflow"); //下溢，退出运行
	return S->data[S->top--];//栈顶元素返回后将栈顶指针减1
}

//取栈顶元素
int StackTop(SeqStack *S)
{
	if(StackEmpty(S))
		Error("Stack is empty");
	return S->data[S->top];
}
