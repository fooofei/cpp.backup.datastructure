#pragma once

#include <iostream>
using namespace std;

template <class T>
class CCycleQueue
{
public:
	CCycleQueue(int initSize= 10)
	{
		m_pdata = new T[initSize];
		m_capacity = initSize;
		m_len = m_top = m_base = 0;

	};
	~CCycleQueue()
	{
		if (m_pdata != NULL)
		{
			delete []m_pdata;
		}
		m_len = -1;
		m_top = m_base = m_capacity = 0;
	};
	bool inline IsEmpty() const 
	{
		return (m_len == 0);
	}
	bool inline IsFull() const
	{
		return ( m_len == m_capacity);
	}
	bool EnQueue( T value)
	{
		if (IsFull())
		{
			return false;
		}
		m_pdata[m_top%m_capacity] = value;
		m_top ++;
		m_len++;
		return true;
	}
	bool DeQueue (T &value)
	{
		if (IsEmpty())
		{
			return false;
		}
		value = m_pdata[m_base++];
		m_base = m_base%m_capacity;
		--m_len;
		return true;
	}
	bool GetBase(T &value)
	{
		if (IsEmpty())
		{
			return false;
		}
		value = m_pdata[m_base];
		return true;
	}

protected:
	T*	m_pdata;
	int m_top;
	int m_base;
	int m_len;
	int m_capacity;
};