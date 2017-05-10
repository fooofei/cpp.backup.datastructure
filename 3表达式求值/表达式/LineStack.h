#pragma once 
#include <iostream>
using namespace std;
#define MAX 10


template <class T>
class LineStack
{
public:
	T *p;
	int Top;
	int Base;
	int iLen;
public:
	LineStack(){};
	~LineStack(){};

	void InitStack();
	void Push(T e );
	void Pop( T &e);
	void GetTop (T &e);
	void FreeStack();
};


template <class T>
void LineStack<T>::InitStack()
{
	p = new T[MAX];
	iLen = Top = Base = 0;
}

template<class T>
void LineStack<T>::Push(T e )
{
	if(Top==MAX)
	{
		e  = *((T*)0);
		return ;
	}
	p[Top] = e;
	Top++;
	iLen++;
}
template <class T>
void LineStack<T>::Pop( T &e)
{
	if(Top==Base)
	{
		e = *((T*)0);
		return ;
	}
	e = p[--Top];
	iLen--;

}
template <class T>
void LineStack<T>::GetTop (T &e)
{
	int i = Top;
	e = p[--i];
}
template <class T>
void LineStack<T>::FreeStack()
{
	if (p!=NULL)
	{
		delete []p;
	}
	iLen=-1;
	Top = Base = 0;
}