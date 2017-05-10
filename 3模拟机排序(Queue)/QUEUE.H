#ifndef QUEUE_H
#define  QUEUE_H
// 2012-9-28 重新修改为模板
// 2014_05_02 加拷贝构造函数、赋值构造函数
// 2014_06_01 再次修改 

#include <stdio.h>
#include <malloc.H>


template<typename T>
class QUEUE
{
protected:

	int m_nBase;
	int m_nTop;
	int m_nLen;
	int m_nCapacity;
	int m_nStepSize;
	T* m_pData;
protected:
public:

	QUEUE(int stepSize = 10)
	{
		m_pData = (T*)malloc(sizeof(T)*stepSize);
		if (NULL == m_pData )
			throw "QUEUE() malloc failed";
		memset(m_pData,0,sizeof(T)*stepSize);
		m_nTop = m_nBase = m_nLen = 0;
		m_nStepSize = m_nCapacity = stepSize;
	}
	~QUEUE() 
	{
		if (NULL != m_pData)
		{
			free(m_pData);
			m_pData = NULL;
			m_nTop = m_nBase = m_nCapacity = m_nStepSize= 0 ;
			m_nLen = -1;
		}
	}
	
	bool enQueue(T Data)
	{
		if (NULL == m_pData)
		{
			return false;
		}
		if (m_nTop==this->m_nCapacity-1)
		{

			m_pData = (T*)realloc(m_pData,sizeof(T)*(m_nCapacity+m_nStepSize));
			if (NULL == m_pData)
			{
				throw "realloc failed";
				return false;
			}
			memset(&m_pData[m_nCapacity],0,sizeof(T)*m_nStepSize);
			m_nCapacity += m_nStepSize;
		}

		m_pData[m_nTop++] = Data;
		++m_nLen;
		return true;
	}
	bool deQueue(T* p)
	{
		if (isEmpty())
		{
			if(p != NULL)
				*p = *(T*)0;  // 这里可能需要更改  
			return false;
		}
		if(p != NULL)
			*p = m_pData[m_nBase];
		++m_nBase;
		--m_nLen;
		return true;
	}
	bool inline isEmpty(void) const 
	{
		return ((m_nBase == m_nTop)|| (NULL == m_pData));
	}
	int inline len(void) const
	{
		if (NULL == m_pData)
		{
			return -1;
		}
		return m_nLen;
	}
	bool traverse(void(*VISIT)(T e))
	{
		if (isEmpty())
		{
			return false;
		}

		int i;

		for (i=m_nBase;i<m_nTop;++i)
		{
			VISIT(m_pData[i]);
		}
		return true;
	}
	bool base(T &Data) const
	{
		if (isEmpty())
		{
			return false;
		}
		Data = m_pData[m_nBase];
	}
	bool top(T &Data)
	{
		if (isEmpty())
		{
			return false;
		}
		Data = m_pData[m_nTop-1];
		return true;
	}
	void clear(void)
	{
		m_nTop = m_nBase = m_nLen = 0;
	}
	  T operator[] (int iIndex) // qq[2]
	  {
		  if (iIndex>=m_nBase &&iIndex<m_nTop)
		  {
			  return m_pData[iIndex];
		  }
		  return *(T*)0;
		  
	  }
  QUEUE& operator = (const QUEUE &q) //  a = b;
  {
	  m_pData = (T*)malloc(sizeof(T)*q.m_nCapacity);
	  if (NULL == m_pData)
		throw "operator = malloc failed";
	  memcpy(m_pData,q.m_pData,sizeof(T)*q.m_nCapacity);
	  this->m_nBase = q.m_nBase;
	  this->m_nCapacity = q.m_nCapacity;
	  this->m_nLen = q.m_nLen;
	  this->m_nStepSize = q.m_nStepSize;
	  this->m_nTop = q.m_nTop;
	  return (*this);
  }
  explicit QUEUE(const QUEUE &qq )
  {
	  m_pData = (T*)malloc(sizeof(T)*q.m_nCapacity);
	  if (NULL == m_pData)
		  throw "operator = malloc failed";
	  memcpy(m_pData,q.m_pData,sizeof(T)*q.m_nCapacity);
	  this->m_nBase = q.m_nBase;
	  this->m_nCapacity = q.m_nCapacity;
	  this->m_nLen = q.m_nLen;
	  this->m_nStepSize = q.m_nStepSize;
	  this->m_nTop = q.m_nTop;
  }
};

#endif//QUEUE_H