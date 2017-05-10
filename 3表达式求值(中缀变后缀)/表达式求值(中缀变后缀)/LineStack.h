#pragma once 
#include <iostream>
using namespace std;
#define MAX 20


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
	T Pop();
	T GetTop ();
	void FreeStack();
	bool IsEmpty();
};

template <class T>
bool LineStack<T>::IsEmpty()
{
	if(Top==Base)
	{
		return true;
	}
	return false;
}
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
		cout<<"Stack Full"<<endl;
		return ;
	}
	p[Top] = e;
	Top++;
	iLen++;
}
template <class T>
T LineStack<T>::Pop()
{
	T e ;
	if(Top==Base)
	{
		e = *((T*)0);
	}
	else
	{
		e = p[--Top];
		iLen--;
	}
	return e;
	

}
template <class T>
T LineStack<T>::GetTop ()
{
	if (IsEmpty())
	{
		return *((T*)0);
	}
	
	int i = Top;
	T e = p[--i];

	return e;
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