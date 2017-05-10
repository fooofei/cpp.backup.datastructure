#ifndef SRANDARRAY_H
#define SRANDARRAY_H


#include <STDIO.H>
#include <WINDOWS.H>
#include <ASSERT.H>
#include <TIME.H>

template <typename ARRAYDATA>
class SRANDARRAY
{
public:
  ARRAYDATA* m_pData;
  int m_iArrayStart;
  int m_iArrayEnd;
public:
  
  void Create(int iStart, int iEnd);
  void Create(void);
  int GetSize(void);
  void Destroy(void);
  void Display(void);
  
};



template <typename ARRAYDATA>
int SRANDARRAY<ARRAYDATA>::GetSize(void)
{
  assert(m_pData!=NULL);

  return m_iArrayEnd-m_iArrayStart+1;
}


template <typename ARRAYDATA>
void SRANDARRAY<ARRAYDATA>::Create(void)
{
  m_iArrayStart = 1;
  m_iArrayEnd = 20;
  
  m_pData = (ARRAYDATA*)malloc(sizeof(ARRAYDATA)*(m_iArrayEnd+1));
  
  assert(m_pData!=NULL);
  
  memset(m_pData,0,sizeof(ARRAYDATA)*(m_iArrayEnd+1));
  
  srand(time(NULL));
  
  int i = 0;
  
  for (i = m_iArrayStart;i<=m_iArrayEnd;++i)
  {
    m_pData[i] = rand()%100;
  }
}



template <typename ARRAYDATA>
void SRANDARRAY<ARRAYDATA>::Create(int iStart, int iEnd)
{
  m_pData = (ARRAYDATA*)malloc(sizeof(ARRAYDATA)*(iEnd+1));
 
  assert(m_pData!=NULL);
  
  memset(m_pData,0,sizeof(ARRAYDATA)*(iEnd+1));
  
  srand(time(NULL));
  
  int i = 0;
  
  for (i = iStart;i<=iEnd;++i)
  {
    m_pData[i] = rand()%100;
  }
  
  m_iArrayStart = iStart;
  
  m_iArrayEnd = iEnd;
}


template <typename ARRAYDATA>
void SRANDARRAY<ARRAYDATA>::Destroy(void)
{
  if (m_pData)
  {
    free(m_pData);
  }
  
  m_pData = NULL;

  m_iArrayEnd = m_iArrayStart = -1;
}


template <typename ARRAYDATA>
void SRANDARRAY<ARRAYDATA>::Display(void)
{
  int i = 0;
  
  for (i=m_iArrayStart;i<=m_iArrayEnd;++i)
  {
    printf("%2d ",m_pData[i]);
  }
  
  printf("\n");
}

#endif // SRANDARRAY_H