#include <iostream>  
#include <stack>  
#include <queue>  
#include <string>  
using namespace std;  

#include "head.h"  

#ifndef FUNC  
#define FUNC  

int pow(int e,int n)   // e 的 n  次方
{
	int i = 0;
	int Result = 1;
	for(i=0;i<n;i++)
	{
		Result = Result*e;
	}
	return Result;
}

//判断是否为运算符,是返回true，否返回false  
bool Is_op(char op)  
{  
	//运算符数组  
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


//返回运算符op所对应的优先级  
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
		//定义: 在栈中的右括号和栈底字符的优先级最低  
		return 0;     
	}  
}  

//释放树  
void Free_tree(TNode *&p)  
{  
	if(p->left != NULL)  
		Free_tree(p->left);  
	if(p->right != NULL)  
		Free_tree(p->right);  
	delete(p);  
}  


//根据后缀表达式生成二叉树  
void Create_tree(TNode *&p,string str)  
{  
	stack<TNode*> nodeStack;  
	char temp;  
	int i = 0;  
	temp = str[i++];  
	//遍历后缀表达式，生成二叉树  
	while(temp != '\0')  
	{  
		//如果不是运算符，则进栈  
		if(!Is_op(temp))  
		{  
			//以temp为结点值构造二叉树结点  
			p = new TNode(temp);  
			//将该结点压入栈中  
			nodeStack.push(p);  
			temp=str[i++];  
		}  
		else  
		{  
			//运算符结点  
			p = new TNode(temp);  
			//若栈非空，则弹栈，并设为运算符结点的右孩子  
			if(nodeStack.size())  
			{  
				p->right = nodeStack.top();  
				nodeStack.pop();  
			}  
			//若栈非空，则弹栈，并设为运算符结点的左孩子  
			if(nodeStack.size())  
			{  
				p->left = nodeStack.top();  
				nodeStack.pop();  
			}  
			//将刚生成的树压入栈中  
			nodeStack.push(p);  
			temp=str[i++];  
		}  
	}  
}  


//先将中缀表达式转换为后缀表达式，再调用Create_tree方法生成二叉树  
void Postfix_exp(TNode *&p, string str)  
{  
	stack<char> a;//运算符栈  
	char temp;//临时存储中缀表达式中的元素  
	string postfixexp="";//存储后缀表达式  
	int i=0;  
	temp = str[i++];  
	//遍历中缀表达式，产生后缀表达式  
	while(temp != '\0')  
	{  
		//如果是操作数，直接添加到后缀表达式  
		if(!Is_op(temp))  
		{  
			postfixexp += temp;  
			temp = str[i++];  
		}  
		//如果是'('，直接入栈  
		else if(temp == '(')  
		{  
			a.push(temp);  
			temp = str[i++];  
		}  
		//如果是')'，将栈中的运算符出栈，直到遇到'('  
		else if(temp == ')')  
		{  
			while(a.top() != '(')  
			{  
				postfixexp += a.top();  
				a.pop();//在碰到'('和栈为空前，反复弹出栈中元素  
			}  
			a.pop();//弹出'('  
			temp = str[i++];  
		}  
		//如果是'+'、'-'、'*'、'/'、'^'  
		else if(temp=='+'||temp=='-'||temp=='*'||temp=='/'||temp=='^')  
		{  
			//若栈非空，栈顶不是左括号，且栈顶元素优先级不低于输入运算符时，将栈顶元素弹出到后缀表达式中  
			while(!a.empty() && a.top()!='(' && Get_priority(a.top()) >= Get_priority(temp))  
			{  
				postfixexp += a.top();  
				a.pop();  
			}  
			//不满足条件时，入栈  
			a.push(temp);  
			temp = str[i++];  
		}  
	}  
	//将栈中剩余的操作符添加到后缀表达式中  
	while(!a.empty())  
	{  
		postfixexp += a.top();  
		a.pop();  
	}  
	//此时，后缀表达式已生成，调用Create_tree方法生成二叉树  
	Create_tree(p,postfixexp);  
}  


//计算树高  
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


//层次遍历打印二叉树  
void Print_tree(TNode *p)  
{  
	int height = Depth_tree(p);//树高  
	int h=0;//树在屏幕中的高度  
	int i;  

	queue<TNode*> aQueue;  
	TNode *pointer = p;//指向队首  
	TNode *lastpointer;//指向队尾  
	if(pointer)//根结点，第1层的第1个位置  
	{  
		pointer->s=1;  
		pointer->t=1;  
		aQueue.push(pointer);  
	}  
	//当队列不空时  
	while(!aQueue.empty())  
	{  
		lastpointer = pointer;  
		pointer=aQueue.front();  
		aQueue.pop();  
		//如果当前结点的高度大于屏幕中树的高度，换行，更新高度  
		if(pointer->s > h)  
		{  
			cout<<endl;  
			h = pointer->s;  
		}  
		//如果当前结点是第1个位置  
		if(pointer->t == 1)  
		{  
			for(i=0; i<pow(2,height-pointer->s)-1; i++)  
				cout<<" ";  
		}  
		//如果当前结点的高度不等于队尾结点的高度  
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
		cout<<pointer->oper;//输出结点元素  
		//若左子树不为空  
		if(pointer->left != NULL)  
		{  
			pointer->left->s = pointer->s+1;  
			pointer->left->t = pointer->t*2-1;  
			aQueue.push(pointer->left);  
		}  
		//若右子树不为空  
		if(pointer->right != NULL)  
		{  
			pointer->right->s = pointer->s+1;  
			pointer->right->t = pointer->t*2;  
			aQueue.push(pointer->right);  
		}  
	}  
}  

#endif  