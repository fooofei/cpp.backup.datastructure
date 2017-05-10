#ifndef STACK_H
#define STACK_H



#include <stdio.h>
#include <malloc.H>
// 想来想去我还是抛弃了我最喜欢的用链表表示栈 因为申请内存释放内存是很费时间的
// 改用数组栈了 

  


template <typename STACKDATATYPE> 
class STACK
{

protected:
	int m_nTop;
	int m_nCapacity;
	STACKDATATYPE* m_pData;
	int m_nStackStepSize;
public:
	// 每一步的加和
  	STACK( int stackStepSize = 5){
		m_pData = (STACKDATATYPE*)malloc(sizeof(STACKDATATYPE)*stackStepSize);
		if (m_pData == NULL)
			throw "STACK() malloc failed";
		
		memset(m_pData,0,sizeof(STACKDATATYPE)*stackStepSize);
		m_nTop = 0;
		m_nCapacity = stackStepSize;
		m_nStackStepSize = stackStepSize;
	};
  	~STACK() {
		if (NULL != m_pData)
		{
			free(m_pData);
			m_pData = NULL;
			m_nTop  = m_nCapacity = m_nStackStepSize = -1;
		}
	};

	
	int inline len(void) const
	{
		if (m_pData == NULL)
		{
			return -1;
		}
		return m_nTop;
	}
	bool push(STACKDATATYPE Data)
	{
		if (m_pData == NULL)
		{
			return false;
		}
		if (m_nTop==m_nCapacity-1)
		{
			m_pData = (STACKDATATYPE*)realloc(m_pData,sizeof(STACKDATATYPE)*(m_nCapacity+m_nStackStepSize));
			if (NULL == m_pData)
				throw "push() realloc failed";
			memset(&m_pData[m_nCapacity],0,sizeof(STACKDATATYPE)*m_nStackStepSize);
			m_nCapacity += m_nStackStepSize;
		}
		m_pData[m_nTop++] = Data;
		return true;
	}
	bool pop(STACKDATATYPE* pData)
	{
		if (isEmpty())
		{
			if (pData != NULL)
			{
				*pData = *(STACKDATATYPE*)0;
			}
			return false;
		}
		if (pData != NULL)
		{
			*pData = m_pData[--m_nTop];
			
		}else{
			--m_nTop;
		}
		return true;
		
	}
	bool top(STACKDATATYPE &Data)
	{
		if (isEmpty())
		{
			Data = *(STACKDATATYPE*)0;
			return false;
		}
		Data = m_pData[--m_nTop];
		++m_nTop;
		return true;
	}
	bool base(STACKDATATYPE &Data) const
	{
		if (NULL == m_pData)
		{
			return false;
		}
		Data = m_pData[0];
		return true;
	}

	bool inline isEmpty(void) const
	{
		return (0== m_nTop) ;
	}
  	
  	

  	STACKDATATYPE operator [](int iIndex) const
	{
		if(iIndex>=0&&iIndex<m_nTop)
			return m_pData[iIndex];
		return (*(STACKDATATYPE*)0);
	}

	explicit STACK (const STACK& s)
	{
		m_nTop = s.m_nTop;
		this->m_nCapacity = s.m_nCapacity;
		this->m_nStackStepSize = s.m_nStackStepSize;
		m_pData = (STACKDATATYPE*)malloc(sizeof(STACKDATATYPE)*m_nCapacity);
		if (NULL == m_pData)
			throw "STACK(const STACK&) malloc failed";
		memcpy(m_pData,s.m_pData,sizeof(STACKDATATYPE)*m_nTop);
	}

	STACK& operator = (const STACK& s)
	{
		this->m_nTop = s.m_nTop;
		this->m_nCapacity = s.m_nCapacity;
		m_pData = (STACKDATATYPE*)malloc(sizeof(STACKDATATYPE)*m_nCapacity);
		if (NULL == m_pData)
			throw "operator = malloc failed";
		
		memcpy(m_pData,s.m_pData,sizeof(STACKDATATYPE)*m_nTop);
		this->m_nStackStepSize = s.m_nStackStepSize;
		return (*this);
	}

	bool traverse(VOID(*VisitFunc)(STACKDATATYPE Data));
};


template <typename STACKDATATYPE>
bool STACK<STACKDATATYPE>::traverse(VOID(*VISIT)(STACKDATATYPE Data))
{
  if (NULL == m_pData)
  {
	  return false;
  }
  int i;
  for (i=0;i<m_nTop;++i)
  {
    VISIT(m_pData[i]);
  }

  return true;
}

#endif //STACK_H