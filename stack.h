#include<iostream>
using namespace std;

#define StackSize 10 //�ٶ�Ԥ�����ջ�ռ����Ϊ100��Ԫ��
//typedef char DataType;//�ٶ�ջԪ�ص���������Ϊ�ַ�
typedef struct
{
	int data[StackSize];//ע�⣬�˴��޶�������ĳ���
    int top;
}SeqStack;

int Pop(SeqStack *S);

void Error(char* message)
{
	cout<<message<<endl;
}

//��ջ��
void InitStack(SeqStack *S)
{	//��˳��ջ�ÿ�
	S->top=-1;
} 

//��ջ��
int StackEmpty(SeqStack *S)
{
	return S->top==-1;
} 

//��ջ��
int StackFull(SeqStack *S)
{
	return S->top==StackSize-1;
} 

//��ջ
void Push(SeqStack *S,int x)
{
	if(StackFull(S))
	{
		Error("Stack overflow"); //���磬�˳�����
		cout<<Pop(S)<<endl;
	}
	S->data[++S->top]=x;//ջ��ָ���1��x��ջ
}

//��ջ
int Pop(SeqStack *S)
{
	if(StackEmpty(S))
		Error("Stack underflow"); //���磬�˳�����
	return S->data[S->top--];//ջ��Ԫ�ط��غ�ջ��ָ���1
}

//ȡջ��Ԫ��
int StackTop(SeqStack *S)
{
	if(StackEmpty(S))
		Error("Stack is empty");
	return S->data[S->top];
}
