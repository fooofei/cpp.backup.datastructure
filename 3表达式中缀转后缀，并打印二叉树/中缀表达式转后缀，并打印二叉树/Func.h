#include <iostream>  
#include <stack>  
#include <queue>  
#include <string>  
using namespace std;  

#include "head.h"  

#ifndef FUNC  
#define FUNC  

int pow(int e,int n)   // e �� n  �η�
{
	int i = 0;
	int Result = 1;
	for(i=0;i<n;i++)
	{
		Result = Result*e;
	}
	return Result;
}

//�ж��Ƿ�Ϊ�����,�Ƿ���true���񷵻�false  
bool Is_op(char op)  
{  
	//���������  
	char oper[]={'(',')','+','-','*','/','^'};  
	for(int i=0; i<sizeof(oper); i++)  
	{  
		if(op == oper[i])  
		{  
			return true;  
		}  
	}  
	return false;  
}  


//���������op����Ӧ�����ȼ�  
int Get_priority(char op)  
{  
	switch(op)  
	{    
	case '(':  
		return 1;  
	case '+':   
	case '-':  
		return 2;  
	case '*':   
	case '/':  
		return 3;  
	case '^':   
		return 4;  
	default:  
		//����: ��ջ�е������ź�ջ���ַ������ȼ����  
		return 0;     
	}  
}  

//�ͷ���  
void Free_tree(TNode *&p)  
{  
	if(p->left != NULL)  
		Free_tree(p->left);  
	if(p->right != NULL)  
		Free_tree(p->right);  
	delete(p);  
}  


//���ݺ�׺���ʽ���ɶ�����  
void Create_tree(TNode *&p,string str)  
{  
	stack<TNode*> nodeStack;  
	char temp;  
	int i = 0;  
	temp = str[i++];  
	//������׺���ʽ�����ɶ�����  
	while(temp != '\0')  
	{  
		//�����������������ջ  
		if(!Is_op(temp))  
		{  
			//��tempΪ���ֵ������������  
			p = new TNode(temp);  
			//���ý��ѹ��ջ��  
			nodeStack.push(p);  
			temp=str[i++];  
		}  
		else  
		{  
			//��������  
			p = new TNode(temp);  
			//��ջ�ǿգ���ջ������Ϊ����������Һ���  
			if(nodeStack.size())  
			{  
				p->right = nodeStack.top();  
				nodeStack.pop();  
			}  
			//��ջ�ǿգ���ջ������Ϊ�������������  
			if(nodeStack.size())  
			{  
				p->left = nodeStack.top();  
				nodeStack.pop();  
			}  
			//�������ɵ���ѹ��ջ��  
			nodeStack.push(p);  
			temp=str[i++];  
		}  
	}  
}  


//�Ƚ���׺���ʽת��Ϊ��׺���ʽ���ٵ���Create_tree�������ɶ�����  
void Postfix_exp(TNode *&p, string str)  
{  
	stack<char> a;//�����ջ  
	char temp;//��ʱ�洢��׺���ʽ�е�Ԫ��  
	string postfixexp="";//�洢��׺���ʽ  
	int i=0;  
	temp = str[i++];  
	//������׺���ʽ��������׺���ʽ  
	while(temp != '\0')  
	{  
		//����ǲ�������ֱ����ӵ���׺���ʽ  
		if(!Is_op(temp))  
		{  
			postfixexp += temp;  
			temp = str[i++];  
		}  
		//�����'('��ֱ����ջ  
		else if(temp == '(')  
		{  
			a.push(temp);  
			temp = str[i++];  
		}  
		//�����')'����ջ�е��������ջ��ֱ������'('  
		else if(temp == ')')  
		{  
			while(a.top() != '(')  
			{  
				postfixexp += a.top();  
				a.pop();//������'('��ջΪ��ǰ����������ջ��Ԫ��  
			}  
			a.pop();//����'('  
			temp = str[i++];  
		}  
		//�����'+'��'-'��'*'��'/'��'^'  
		else if(temp=='+'||temp=='-'||temp=='*'||temp=='/'||temp=='^')  
		{  
			//��ջ�ǿգ�ջ�����������ţ���ջ��Ԫ�����ȼ����������������ʱ����ջ��Ԫ�ص�������׺���ʽ��  
			while(!a.empty() && a.top()!='(' && Get_priority(a.top()) >= Get_priority(temp))  
			{  
				postfixexp += a.top();  
				a.pop();  
			}  
			//����������ʱ����ջ  
			a.push(temp);  
			temp = str[i++];  
		}  
	}  
	//��ջ��ʣ��Ĳ�������ӵ���׺���ʽ��  
	while(!a.empty())  
	{  
		postfixexp += a.top();  
		a.pop();  
	}  
	//��ʱ����׺���ʽ�����ɣ�����Create_tree�������ɶ�����  
	Create_tree(p,postfixexp);  
}  


//��������  
int Depth_tree(TNode *t)  
{  
	int depthval,depthleft,depthright;  
	if(t == NULL)  
		depthval = 0;  
	else{  
		depthleft = Depth_tree(t->left)  ;  
		depthright = Depth_tree(t->right);  
		depthval = 1 + (depthleft > depthright ? depthleft : depthright);  
	}  
	return depthval;  
}  


//��α�����ӡ������  
void Print_tree(TNode *p)  
{  
	int height = Depth_tree(p);//����  
	int h=0;//������Ļ�еĸ߶�  
	int i;  

	queue<TNode*> aQueue;  
	TNode *pointer = p;//ָ�����  
	TNode *lastpointer;//ָ���β  
	if(pointer)//����㣬��1��ĵ�1��λ��  
	{  
		pointer->s=1;  
		pointer->t=1;  
		aQueue.push(pointer);  
	}  
	//�����в���ʱ  
	while(!aQueue.empty())  
	{  
		lastpointer = pointer;  
		pointer=aQueue.front();  
		aQueue.pop();  
		//�����ǰ���ĸ߶ȴ�����Ļ�����ĸ߶ȣ����У����¸߶�  
		if(pointer->s > h)  
		{  
			cout<<endl;  
			h = pointer->s;  
		}  
		//�����ǰ����ǵ�1��λ��  
		if(pointer->t == 1)  
		{  
			for(i=0; i<pow(2,height-pointer->s)-1; i++)  
				cout<<" ";  
		}  
		//�����ǰ���ĸ߶Ȳ����ڶ�β���ĸ߶�  
		else if(lastpointer->s != pointer->s)  
		{  
			for(i=0; i<(pointer->t-1)*(pow(2,height-pointer->s+1)-1)+(pointer->t-1)-1+pow(2,height-pointer->s); i++)  
				cout<<" ";  
		}  
		else   
		{  
			for(i=0; i<(pointer->t-lastpointer->t)*(pow(2,height-pointer->s+1)-1)+(pointer->t-lastpointer->t)-1; i++)  
				cout<<" ";  
		}  
		cout<<pointer->oper;//������Ԫ��  
		//����������Ϊ��  
		if(pointer->left != NULL)  
		{  
			pointer->left->s = pointer->s+1;  
			pointer->left->t = pointer->t*2-1;  
			aQueue.push(pointer->left);  
		}  
		//����������Ϊ��  
		if(pointer->right != NULL)  
		{  
			pointer->right->s = pointer->s+1;  
			pointer->right->t = pointer->t*2;  
			aQueue.push(pointer->right);  
		}  
	}  
}  

#endif  