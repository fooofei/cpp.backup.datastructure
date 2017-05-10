//********************************************************************
//    �������ǵݹ�����㷨�ܼ�.CPP    �ļ�ע��
//    FileName   :    �������ǵݹ�����㷨�ܼ�.CPP
//    FilePath   :    
//    Author     :    
//    CreateTime :    2013/5/1 14:15
//    ModifyTime :    2013/5/15
//    Description:    ��������˼· ���Ǹ�ϰ
// 
// 1. �ݹ����û�м�������  ����ı��� ȫ�Ƿǵݹ�� 
// 2. ��Ҫ�õ���ջ�Ͷ��� ȫ��STL ���Լ�ʵ�� ��Ϊ������Ҫ��ϰ�㷨
// 3. Ӣ��:ǰ��PreOrder ���� infix order  ���� postorder
// 4. ���������1�������������û�а�������Ĵ����,Ϊ���д���,���� ����  ջ ����,ʵ��������� 
// 5. �ǵݹ�ջ���� ���������� �ͳ�ĵݹ�����������ķ���   �����ı��� 
//				���Ǳ�����˳����ԭ����˳�� �ǲ��ܱ��ı��
// 6. ����������Ѷ������� ����������Ѷ�����С��
// 7. ���ټ�֮�� �ܶ��㷨��Ŷ ����ʢ��
// 8. ���ӷǵݹ鲻ʹ��ջ�ķ���(��ת����������������http://blog.csdn.net/stund/article/details/7541829)
//*********************************************************************
#include <stdio.h>
#include <QUEUE>
#include <WINDOWS.H>
#include <stack>

using namespace std;



typedef struct tagBTNODE
{
	char Data;
	struct tagBTNODE * pRNext;
	struct tagBTNODE* pLNext;
}BTNODE,*PBTNODE;


void CreateTreeFromFile(PBTNODE &pRoot , FILE** pfp);
void CreateTree(PBTNODE &pRoot);

void PreOrderTraverse(PBTNODE pRoot);
void PreOrderTraverse2(PBTNODE pRoot); // �Ƽ� ������������ �ü���
void PreOrderTraverse3(PBTNODE pRoot); // �Ƽ� ������ı����㷨���� �ܳ�����


void InOrderTraverse(PBTNODE pRoot);
void InOrderTraverse2(PBTNODE pRoot);
void InOrderTraverse3(PBTNODE pRoot); // �Ƽ�
void InOrderTraverse4(PBTNODE pRoot); // Morris����

void LevelOrderTraverse(PBTNODE pRoot);

void PosOrderTraverse(PBTNODE pRoot);
void PosOrderTraverse2(PBTNODE pRoot); // �Ƽ�
void PosOrderTraverse3(PBTNODE pRoot);
void PosOrderTraverse4(PBTNODE pRoot);

void DestroyTree(PBTNODE &pRoot);

int GetBiTreeDepth(PBTNODE pRoot);

// ��bad  �ؼ��ֵı������� �޸��˶������Ľṹ ��ô���ǲ������ͷŶ�����
//                       Ҫ�ͷŶ�������Ҫ����ÿ�����ĵ�ַ

// �������漸���йؼ���bad ���㷨,������һ���ļ��и������䲻bad��ʵ��
//         �����޸���ջ�������������,���ٱ������ַ,���Ǳ�����ȫ��

void InOrderTraverse_bad(PBTNODE pRoot);
void PosOrderTraverse_bad(PBTNODE pRoot);
int main()
{


	PBTNODE pRoot;

	//CreateTree(pRoot );

	FILE * fp = fopen("tree.txt" , "r");

    if(fp == NULL)
        return 0;
	CreateTreeFromFile(pRoot , &fp);

	fclose(fp);


	printf("PreOrderTraverse:    ");
	PreOrderTraverse(pRoot );

	printf("PreOrderTraverse2:   ");
	PreOrderTraverse2(pRoot);

    printf("PreOrderTraverse3:   ");
	PreOrderTraverse3(pRoot);

    printf("----------------------------------------\n");
    

	printf("LevelOrderTraverse:  ");
	LevelOrderTraverse(pRoot);

    printf("----------------------------------------\n");
    
	printf("InOrderTraverse:     ");
	InOrderTraverse( pRoot );
    
    printf("InOrderTraverse2:    ");
    InOrderTraverse2( pRoot );

    printf("InOrderTraverse3:    ");
    InOrderTraverse3( pRoot );

    printf("InOrderTraverse4:    ");
    InOrderTraverse4( pRoot );


// 	printf("InOrderTraverse_bad: ");
// 	InOrderTraverse_bad(pRoot);

    printf("----------------------------------------\n");
    
   
//	printf("PosOrderTraverse_bad:");
//	PosOrderTraverse_bad(pRoot);

    printf("PosOrderTraverse:    ");
    PosOrderTraverse( pRoot );

    printf("PosOrderTraverse2:   ");
    PosOrderTraverse2( pRoot );

    printf("PosOrderTraverse3:   ");
    PosOrderTraverse3( pRoot );

    printf("PosOrderTraverse4:   ");
    PosOrderTraverse4( pRoot );

    printf("----------------------------------------\n");

    printf("Before Destroy Test: ");
	LevelOrderTraverse(pRoot);
	DestroyTree( pRoot );

	return 0;
}




// Morris����  (Robson���� ��Ҫ�� �ܸ��� ���� �ҵ��Ļ�����)
// ���� ����Ҫջ�Ŀռ�  ֻ��Ҫһ����ʱ�Ľ��ָ��
void InOrderTraverse4(PBTNODE pRoot)
{
    PBTNODE pBTNodeTemp = NULL;
    while (pRoot != NULL)
    {
        if(NULL == pRoot->pLNext)
        {
            printf("%c ",pRoot->Data);
            pRoot = pRoot->pRNext ;
        }
        else
        {
            pBTNodeTemp = pRoot->pLNext;
            while (NULL != pBTNodeTemp->pRNext && pRoot != pBTNodeTemp->pRNext)
            {
                pBTNodeTemp = pBTNodeTemp->pRNext;
            }
			if(pBTNodeTemp->pRNext == NULL)
			{
				pBTNodeTemp->pRNext = pRoot;
				pRoot = pRoot ->pLNext;
			}
			else
			{
				printf("%c ",pRoot->Data);
				pBTNodeTemp->pRNext = NULL;
				pRoot = pRoot->pRNext;
			}
        }
    }

    printf("\n");
}


// �ݹ鴴���� ����Ϊ���ļ� ����ÿ��������ȥ�ֶ���������

void CreateTreeFromFile(PBTNODE &pRoot , FILE** pfp)
{
	char data;
	
	fscanf(*pfp ," %c" , &data );
	
	if (data == ('#'))
	{
		pRoot = NULL;
	}
	else
	{
		pRoot = (PBTNODE )malloc(sizeof(BTNODE ));
		pRoot->Data = data;
		
		CreateTreeFromFile(pRoot->pLNext , pfp );
		CreateTreeFromFile(pRoot->pRNext , pfp );
	}
}

 // û�м�������
void CreateTree(PBTNODE &pRoot)
{
	char data;

	scanf(" %c" , &data );

	if (data == int('#'))
	{
		pRoot = NULL;
	}
	else
	{
		pRoot = (PBTNODE )malloc(sizeof(BTNODE ));
		pRoot->Data = data;

		CreateTree( pRoot->pLNext );
		CreateTree( pRoot->pRNext );
	}
}

int GetBiTreeDepth(PBTNODE pRoot)
{
    if( pRoot == NULL)
        return 0;

    return max(GetBiTreeDepth(pRoot->pLNext)+1 , GetBiTreeDepth(pRoot->pRNext)+1);
}


// ǰ�����
// �õ������ݽṹ: ջ
// ���� 1. ����ջ
//      2. ѭ�� ջ����
//         2.1 ��ջ ��Ϊ�����
//         2.2 ѭ�� ������㲻Ϊ��
//              2.2.1 ������������
//              2.2.2 �Һ�����ջ ���ù��Ƿ�ΪNULL
//              2.2.3 ��������¸�ֵָ������
void PreOrderTraverse(PBTNODE pRoot)
{
	if(pRoot == NULL)
		return;

	stack<PBTNODE> s;
	// ����ջ
	s.push(pRoot);

	//ѭ�� ջ����
	while(!s.empty())
	{
		// ��ջ ��Ϊ�����
		pRoot = s.top();
		s.pop();
	
		// ѭ�� ������㲻Ϊ��
		while(pRoot != NULL)
		{
			// ������������
			printf("%c ",pRoot->Data);
			// �Һ�����ջ ���ù��Ƿ�ΪNULL
			s.push(pRoot->pRNext);
			// ��������¸�ֵָ������
			pRoot = pRoot->pLNext;
		}
	}

	printf("\n");
}

// ǰ����� 2 (�Ƽ�  ��Ϊ������������ �ü���)
// �õ������ݽṹ:ջ
// ���� 1. ����ջ
//      2. ѭ��ջ����
//         2.1. ȡ������ ���
//         2.2. ��������Һ��� �Һ�����ջ �������� ������ջ


// ���������Ľṹ������
void PreOrderTraverse2(PBTNODE pRoot)
{
	if(pRoot == NULL )
		return;

	stack<PBTNODE> s;
 // ����ջ
	s.push(pRoot);

	// ѭ��ջ����
	while(!s.empty())
	{
		// ��ջ��Ҫ������������...Orz...
		// ȡ������ ���
		pRoot = s.top();
		s.pop();
		printf("%c ",pRoot->Data );

		// �����Һ��� �Һ�����ջ �������� ������ջ
		if(pRoot->pRNext != NULL)
			s.push(pRoot->pRNext );
		if(pRoot->pLNext != NULL )
			s.push( pRoot->pLNext );
	}

	printf("\n");
}


void PreOrderTraverse3(PBTNODE pRoot)
{
    if( pRoot == NULL )
        return;

    stack<PBTNODE> s;

    while ( pRoot != NULL || !s.empty() )
    {
        while ( pRoot != NULL )
        {
            printf("%c ", pRoot->Data );
            s.push(pRoot);

            pRoot = pRoot->pLNext ;
        }

        pRoot = s.top();
        s.pop();

        pRoot = pRoot->pRNext ;
    }
    printf("\n");
}

// ���֮�� InOrderTraverse2 �����

void InOrderTraverse(PBTNODE pRoot)
{
	if(pRoot == NULL)
		return;

	stack<PBTNODE> s;

	while (pRoot !=NULL)
	{
	
		while ( pRoot->pLNext != NULL )
		{
			s.push(pRoot);
			pRoot = pRoot->pLNext;
		}

		printf("%c ",pRoot->Data );
		
		pRoot = NULL;   

		while (!s.empty())
		{
			pRoot = s.top();
			s.pop();
			if (pRoot != NULL)
				printf("%c ",pRoot->Data );
			if(pRoot ->pRNext != NULL)
			{
				pRoot = pRoot->pRNext;
				break;
			}
		}

		
	}

	printf("\n");
}


// �Ƽ����� 
// ��ε���α�����һ���������������(ע�� ֻ����һ������)

// �õ������ݽṹ: ջ
// ���� 1. ѭ�� ����㲻Ϊ�� ���� ջ����
//          1.1 ����㲻�� ��ջ �����ָ������
//          1.2 �����Ϊ��   
//             1.2.1 ȡ�������Ϊ�µĸ����
//             1.2.2 �������
//             1.2.3 �����ָ���Һ��� ��ʱ�ĸ����һ��û�������� (Ϊʲô?��Ϊ�������������.)

void InOrderTraverse2(PBTNODE pRoot)
{
    // ��ʼ�����ж� pRoot == NULL  ע�⵽��û
    stack<PBTNODE> s;
    
    // ѭ�� ����㲻Ϊ�� ���� ջ����
    while( pRoot != NULL || !s.empty() )
    {
        // ����㲻�� ��ջ �����ָ������ 
         if( pRoot != NULL )
         {
               s.push(pRoot);
               pRoot = pRoot->pLNext;
         }
         // �����Ϊ��   
         else
         {
             // ȡ�������Ϊ�µĸ���� 
             pRoot = s.top();
             s.pop();

             // �������
             printf("%c ",pRoot->Data );

             // �����ָ���Һ��� ��ʱ�ĸ����һ��û��������
             pRoot = pRoot->pRNext;
         }
    }

	printf("\n");
}


// �Ƽ�
// Ӧ�ÿ�����InOrderTraverse �ĸĽ��ͼ�
// ������ ��InOrderTraverse2�Ľṹ�Ǻ����Ƶ�  ���� �˼����治��whileѭ��
void InOrderTraverse3(PBTNODE pRoot)
{
    if(pRoot == NULL)
        return;
    
    stack<PBTNODE> s;
    while ( pRoot != NULL || !s.empty())
    {
        while ( pRoot !=NULL )
        {
            s.push( pRoot );
            pRoot = pRoot->pLNext ;
        }

        pRoot = s.top();
        s.pop();

        printf("%c " , pRoot->Data );
        pRoot = pRoot->pRNext ;
    }

    printf("\n");
}


// bad ���ǲ��Ƽ�ʹ�� �ܻ��ķ���
// �������� ����֮�� ��ı�������Ľṹ
// �⾹Ȼ�����Լ��뵽���㷨,�þ���.ԭ����ԭ����ʦû������㷨,���Ծ������ʦ����,�������

// �õ������ݽṹ:ջ
// ����: 1. ����ջ
//       2. ջ���� ѭ��
//          2.1 ��ջ ����Ľ�㱣���ջ�������ӵ�ַ
//          2.2 ������(��Ϊ��) ����ϲ���ջ�Ľ�� 
//          2.3 ������ ��ջ�������Ӹ�ֵΪ��
//               2.3.1 �����Һ��� �Һ�����ջ
//               2.3.2 2.1����ջ�Ľ����ջ  ����������ӵ�ַ��ջ 
void InOrderTraverse_bad(PBTNODE pRoot)
{
	if(pRoot == NULL)
		return;

	stack<PBTNODE> s;

	PBTNODE pLNext = NULL ;
	// ����ջ
	s.push(pRoot);

	// ջ���� ѭ��
	while(!s.empty())
	{
		// ��ջ ����Ľ�㱣���ջ�������ӵ�ַ
		pRoot = s.top();
		s.pop();
		pLNext = pRoot->pLNext;


		// ������(��Ϊ��) ����ϲ���ջ�Ľ�� 
		if(pLNext == NULL)
			printf("%c ",pRoot->Data );

		// ������ ��ջ�������Ӹ�ֵΪ��
		else
		{
			pRoot->pLNext = NULL;
			// �����Һ��� �Һ�����ջ
			if(pRoot->pRNext != NULL )
				s.push(pRoot->pRNext );

			// ��ջ�Ľ����ջ  ����������ӵ�ַ��ջ 
			s.push(pRoot);
			s.push(pLNext);
		}
	}

	printf("\n");
}

// 2012-9-3 ��������һ�������ҵ������µ��㷨  �Ƕ��ϴ�ѧ�� ������Ŀ¼��
// �ļ�Ϊ:"���Ͷ�������������ǵݹ��㷨.pdf"
// 
// �������Ҫ��ǰ�����Ҫ��Ϥ ,��Ϊ���㷨��˼����ǰ������ķ���

// �õ������ݽṹ:ջ
// ���� 1. ��������ջ(��ջ�͸���ջ) ������ջ
//      2. ѭ�� ��ջ����
//         2.1 ����ջ ��Ϊ�����
//         2.2 ѭ�� ������㲻Ϊ��
//              2.2.1 �������ѹ�븨��ջ
//              2.2.2 ��������ջ ���ù��Ƿ�ΪNULL
//              2.2.3 ��������¸�ֵָ���Һ���
void PosOrderTraverse(PBTNODE pRoot)
{
    if( pRoot == NULL )
        return ;

    stack<PBTNODE> s;
    stack<PBTNODE> sLRM; // ����ջ

    s.push( pRoot );

    while(! s.empty() )
    {
        pRoot = s.top();
        s.pop();

        while( pRoot != NULL )// �˷�������һ�ݱ�ֽ  ����˼��
        {
            // printf("%c ", pRoot->Data );
               
            // ������ǰ�������������� ���ǲ���� �ŵ���һ��ջ��ȥ
            sLRM.push( pRoot );

            // ����� ��ջ���� �����ָ���Һ�����ǰ�����Ҳ��ͬ��
            s.push( pRoot->pLNext );
            pRoot = pRoot->pRNext;
        }
    }

    while( !sLRM.empty() )
    {
        pRoot = sLRM.top();
        sLRM.pop();

        printf("%c ", pRoot->Data );
    }

    printf("\n");
}


// ���Ƽ�
// �����ҽ��ϱߵ� PosOrderTraverse ����Ϊ�������ķ�ʽ��


// �õ������ݽṹ:ջ
// ���� 1. ��������ջ(��ջ�͸���ջ) ������ջ
//      2. ѭ�� ��ջ����
//         2.1. ȡ����ջ���� ���븨��ջ
//         2.2. ����������� ��������ջ �����Һ��� ��������ջ

void PosOrderTraverse2(PBTNODE pRoot)
{
    if( pRoot == NULL )
        return ;

    stack<PBTNODE> s;
    stack<PBTNODE> sLRM;

    s.push( pRoot );

    while ( !s.empty() )
    {
        pRoot = s.top();
        s.pop();

        //printf("%c ",pRoot->Data );
        sLRM.push( pRoot );

        //if( pRoot ->pRNext != NULL)
         //   s.push(pRoot->pRNext);
        //if(pRoot->pLNext != NULL )
        //    s.push( pRoot->pLNext );

        if( pRoot->pLNext != NULL)
            s.push( pRoot->pLNext );
        if( pRoot->pRNext != NULL)
            s.push( pRoot->pRNext );
    }


    while (! sLRM.empty())
    {
        pRoot = sLRM.top();
        sLRM.pop();
        printf("%c ", pRoot->Data );
    }
    printf("\n");
}

// ����һ�ַ���  ��ջ�з����ָ�������� �Ǵ������ƶ������ڵ㻹�Ǵ��Һ����ƶ��ĸ��ڵ�
// �ޱ�Ǳ���
void PosOrderTraverse3(PBTNODE pRoot)
{
    if(pRoot == NULL)
        return;
    stack<PBTNODE> s;

    while (true)
    {
        while (pRoot != NULL )
        {
            s.push( pRoot );
            pRoot = pRoot ->pLNext;
        }

        pRoot = s.top();

        while ( pRoot == NULL)
        {
            s.pop();

            pRoot = s.top();
            s.pop();

            printf("%c ", pRoot->Data );

            if(s.empty())
            {
                printf("\n");
                return;
            }

            pRoot = s.top();
        }

        s.push(NULL);
        pRoot = pRoot ->pRNext ;
    }
}

// ��һ����Ǳ���������Ƿ���ʹ� �˷ѿռ�
// ��־����Ĵ�СҲ����Ҫ�������Ĵ�С���ĵ�
// �㷨�Ƚϸ���  ���Ƽ� 

void PosOrderTraverse4(PBTNODE pRoot)
{
    if( pRoot == NULL )
        return;

    boolean bFlag[20]; 
    stack<PBTNODE> s;
    
    while ( pRoot != NULL )
    {
        s.push( pRoot );
        bFlag[s.size()] = false;
        pRoot = pRoot->pLNext;
    }

    while ( !s.empty() )
    {
        pRoot = s.top();
        if ( pRoot->pRNext != NULL && !bFlag[s.size()])
        {
            bFlag[s.size()] = true;
            pRoot = pRoot->pRNext;

            while ( pRoot != NULL )
            {
                s.push( pRoot );
                bFlag[s.size()] = false;
                pRoot = pRoot->pLNext;
            }
        }

        pRoot = s.top();
        s.pop();

        printf("%c ",pRoot->Data );
    }
    printf("\n");
}

// bad ���ǲ��Ƽ�ʹ�� �ܻ��ķ���
// �������� ����֮�� ��ı�������Ľṹ

// �õ������ݽṹ:ջ
// ����: 1. ����ջ
//       2. ѭ��ջ����
//          2.1 ��ջ ��Ϊ�����
//          2.2 �ж������Һ��� �������
//          2.3 ������һ������
//              2.3.1 ������ ���Һ��ӵĵ�ַ  ���ҽ����������Һ���ָ�븳ֵΪ��
//              2.3.2 ���������ջ
//              2.3.3 ���� �Һ���  �Һ�����ջ   ��������  ���� ��ջ
void PosOrderTraverse_bad(PBTNODE pRoot)
{

	if(pRoot == NULL )
		return ;

	PBTNODE pLNext = NULL , pRNext = NULL;

	stack<PBTNODE> s;
	// ����ջ
	s.push(pRoot);

	// ѭ�� ջ����
	while (!s.empty())
	{
		// ��ջ
		pRoot = s.top();
		s.pop();

		// ���� ���Һ���ʱ   �������
		if(pRoot->pLNext == NULL && pRoot->pRNext == NULL)
			printf("%c ",pRoot->Data );

		// ��������һ������
		else
		{
			// ������ ���Һ��ӵĵ�ַ  ���ҽ����������Һ���ָ�븳ֵΪ��
			pLNext = pRoot->pLNext;
			pRoot->pLNext = NULL;
			
			
			pRNext = pRoot->pRNext;
			pRoot->pRNext = NULL;
			

			// ���������ջ
			s.push(pRoot);

			// ���� �Һ���  �Һ�����ջ   ��������  ���� ��ջ   
			if(pRNext != NULL)
				s.push(pRNext);

			if(pLNext != NULL)
				s.push(pLNext);
		}
		
	}

	printf("\n");
}



// ��������õ������ݽṹ:����
// ���� 1. �����
//      2. ѭ�����в���
//          2.1. ȡ������ ���
//          2.2. ������ ������� ���Һ��� �Һ������

void LevelOrderTraverse(PBTNODE pRoot)
{
	if(pRoot == NULL)
		return;

	queue<PBTNODE> q;
  // �����
	q.push(pRoot);

	// ѭ�����в���
	while (!q.empty())
	{
		// ȡ������ ���
		pRoot = q.front();
		q.pop();
		printf("%c ",pRoot->Data );
		
		// ������ ������� ���Һ��� �Һ������
		if (pRoot->pLNext != NULL)
		  q.push(pRoot->pLNext);
		if(pRoot->pRNext != NULL)
			q.push(pRoot ->pRNext );
	}

	printf("\n");
}


void DestroyTree(PBTNODE &pRoot)
{
	if (pRoot != NULL)
	{
		DestroyTree(pRoot->pLNext );
		DestroyTree( pRoot->pRNext );
		free(pRoot );
		pRoot = NULL;
	}
}