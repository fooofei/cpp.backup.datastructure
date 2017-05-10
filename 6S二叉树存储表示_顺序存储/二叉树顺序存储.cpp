//********************************************************************
//    ������˳��洢.CPP    �ļ�ע��
//    FileName   :    ������˳��洢.CPP
//    FilePath   :    
//    Author     :    
//    CreateTime :    2013/5/3 20:09
//    Description:    ��д ɾȥ��ǰ�Ĵ���  �����Ǵ����ع�
// 1.-1 Ϊ������ Ϊ��
// 2.��ԭ��������0 ��ʼ ��Ϊ���ڵĴ�����Ԫ��1 ��ʼ
// 3.˳��洢һ��ֻ������ȫ������
// 4.��һ����0 ��ʼ��������  ÿһ����˫�׾��� (i+1)/2-1 
// 5.��0��ʼ��������ÿһ������Ӿ��� 2*i+1  �Һ��Ӿ���2*i+2
// 6.�������и����Ĵ��� ����MAX �����ֵС��ʱ�� �ͺ����������е�
//      �ڵ�û�к��� �������ǻ�һ��������ж���û�к��� ���������Խ��
// 7.���ڴ��������� 1- ARRAY_START��ʱ�� ʡȥ���� ������Ϊ�˼�������0 
//       �ʹ�1��ʼ���������д��
// 8.��21������
//*********************************************************************
#include <STDIO.H>
#include <MATH.H>
#include <QUEUE>

using namespace std;


typedef struct tagPOSITION
{
    int iLevel;
    int iOrder;
}POSITION;

const unsigned int  ARRAY_SIZE  =  100  ;  // ����ɶ���������Ĵ�С

// ������ ֻ��ѡһ��
//#define  ARRAY_START_ZERO  0// �����0 ��ʼ
#define  ARRAY_START_ONE  1// �����1 ��ʼ


#ifdef ARRAY_START_ZERO
    #define ARRAY_START ARRAY_START_ZERO
#endif
#ifdef ARRAY_START_ONE
    #define ARRAY_START ARRAY_START_ONE
#endif



// ��ʼ������ȫ��Ϊ-1
void InitArray(int* piArray);
// �������������ĳ���
int CreateBiTree( int *piArray);
// ���շ���true   ���շ���false
bool IsBiTreeEmpty(int *piArray);

// ����: piArray����ָ��
//     : iArraySize ����Ĵ�С ��CreateBiTree�ķ���ֵ
// ����: �����ɶ����������
int GetBiTreeDepth(int *piArray , int iArraySize);

// ����:
//       piArray ����ָ��
//       iElem ���صĶ������ĸ�
// ����: �Ƿ�ɹ� 
bool GetRoot( int* piArray , int* piElem);

// ����:
//       piArray ����ָ��
//       p Ԫ���ڶ�������λ��
// ����: Ԫ��ֵ
int GetElem(int *piArray , POSITION p);

// ����:
//       piArray ����ָ��
//       p Ԫ���ڶ�������λ��
//       iAssignValueԪ�ص���ֵ
// ����: ��
void Assign(int *piArray , POSITION p , int iAssignValue);

// ����:
//       piArray ����ָ��
//       iArraySize �������Ч��С
//       iElem ĳ��Ԫ�ص�ֵ
// ����: ���׵�ֵ,û�и��׷���-1
int GetParent(int* piArray ,int iArraySize , int iElem);

// ����:
//       piArray ����ָ��
//       iArraySize �������Ч��С
//       iElem ĳ��Ԫ�ص�ֵ
// ����: ���ӵ�ֵ,û�����ӷ���-1
int GetLeftChild(int* piArray, int iArraySize ,int iElem);

// ����:
//       piArray ����ָ��
//       iArraySize �������Ч��С
//       iElem ĳ��Ԫ�ص�ֵ
// ����: �Һ��ӵ�ֵ,û���Һ��ӷ���-1
int GetRightChild(int* piArray, int iArraySize ,int iElem);

// ����:
//       piArray ����ָ��
//       iArraySize �������Ч��С
//       iElem ĳ��Ԫ�ص�ֵ
// ����: ���ֵܵ�ֵ,û�����ֵܷ���-1
int GetLeftSibling(int* piArray , int iArraySize , int iElem);

// ����:
//       piArray ����ָ��
//       iArraySize �������Ч��С
//       iElem ĳ��Ԫ�ص�ֵ
// ����: ���ֵܵ�ֵ,û�����ֵܷ���-1
int GetRightSibling(int* piArray , int iArraySize , int iElem);

// ��q�ƶ���T
// ����:
//        q �ƶ�����ĵ�ַ
//        j ���ƶ�����q�е�λ��
//        T ��������ĵ�ַ
//        i �ڽ�������T�е�λ��
//����: ��
void Move (int *q , int j , int *T , int i);

// ����
//     piArray Ŀ������ĵ�ַ
//     iArray �������Ч��С
//     iElem Ҫ�����Ԫ��,�佫������
//     bLeftOrRight �ǵ�������(0)�����Һ��� (1)
//     pInsert��Ҫ����������ַ, ��������
// ����:��
void InsertChild(int *piArray ,int iArraySize, int iElem , bool bLeftOrRight ,int *pInsert);

// ����
//     piArray ����˵��
//     p  ɾ��Ԫ�صĸ���
//     bLeftOrRight��ɾ��������(0)�����Һ��� (1)

void DeleteChild( int *piArray , POSITION p, bool bLeftOrRight );


// ���涼�Ǵ�ӡ���� 

// ������� ��������������
void LevelDisplay(int* piArray , int iArraySize);

void DisplayArray(int *piArray , int iArraySize);

void PreOrderTraverse(int* piArray , int index);

void InOrderTraverse(int* piArray , int index );

void PosOrderTraverse(int* piArray , int index );

void LevelOrderTraverse(int* piArray);
int main( )
{

    int iArray[ARRAY_SIZE] ;
    InitArray(iArray);
    int iArraySize = CreateBiTree(iArray);
    printf("������������,���շ�%d(1:�� 0:��) �������=%d\n",IsBiTreeEmpty(iArray),
        GetBiTreeDepth(iArray , iArraySize));

    int iElem;

    bool bOk = GetRoot(iArray , &iElem );

    if(bOk)
        printf("�������ĸ�Ϊ:%d.\n",iElem);
    else
        printf("�������ǿյ�,û�и�.\n");

    printf("�������������:");
    LevelOrderTraverse(iArray );

    printf("ǰ�����������:");
    PreOrderTraverse( iArray , ARRAY_START );
    printf("\n");

    printf("�������������:");
    InOrderTraverse( iArray , ARRAY_START );
    printf("\n");

    printf("�������������:");
    PosOrderTraverse( iArray , ARRAY_START );
    printf("\n");

    POSITION p;
    p.iLevel = 3;
    p.iOrder = 2;

    if( p.iOrder > (int)pow(2 , p.iLevel-1))
        exit(0);

    printf("��%d��,��%d��Ϊ%d.--�޸�Ϊ-->110.\n",p.iLevel , p.iOrder , GetElem(iArray,p));
  
    Assign(iArray , p ,110 );

    printf("��%d��,��%d��Ϊ%d.\n",p.iLevel , p.iOrder , GetElem(iArray,p));

    
    iElem = 110;

    printf("���%d��˫��Ϊ%d,����Ϊ%d,�Һ���Ϊ%d,���ֵ�Ϊ%d,���ֵ�Ϊ%d.\n" , iElem ,
        GetParent(iArray ,iArraySize , iElem),
        GetLeftChild( iArray , iArraySize , iElem),
        GetRightChild(iArray ,iArraySize , iElem ),
        GetLeftSibling(iArray , iArraySize , iElem ),
        GetRightSibling(iArray , iArraySize ,iElem ));
    
    printf("�������:");
    DisplayArray( iArray , iArraySize );
    return 0;
}

void LevelOrderTraverse(int* piArray)
{
    queue<int> q;

    q.push(ARRAY_START);

    int i;
    while ( !q.empty())
    {
        i = q.front();
        q.pop();

        printf("%d ",piArray[i]);

        if(piArray[2*i +(1-ARRAY_START)] != -1)
            q.push(2*i +(1-ARRAY_START));

        if(piArray[2*i +1 + (1-ARRAY_START)] != -1)
            q.push( 2*i +1 + (1-ARRAY_START) );
    }

    printf("\n");
}


void PosOrderTraverse(int* piArray , int index )
{
    if(piArray[index] != -1)
    {
        
        
        if(piArray[2*index +(1-ARRAY_START)] != -1 )
            PreOrderTraverse(piArray , 2*index +(1-ARRAY_START));
        
        if(piArray[2*index +1+(1-ARRAY_START)] != -1  )
            PreOrderTraverse(piArray ,2*index +1+(1-ARRAY_START) );
    
         printf("%d ",piArray[index]);
    }
}


void InOrderTraverse(int* piArray , int index )
{
    if(piArray[index] != -1)
    {
       
        
        if(piArray[2*index +(1-ARRAY_START)] != -1 )
            PreOrderTraverse(piArray , 2*index +(1-ARRAY_START));
        
         printf("%d ",piArray[index]);

        if(piArray[2*index +1+(1-ARRAY_START)] != -1  )
            PreOrderTraverse(piArray ,2*index +1+(1-ARRAY_START) );
    }
    
}

void PreOrderTraverse(int* piArray , int index)
{
    if(piArray[index] != -1)
    {
        printf("%d ",piArray[index]);

        if(piArray[2*index +(1-ARRAY_START)] != -1 )
            PreOrderTraverse(piArray , 2*index +(1-ARRAY_START));

        if(piArray[2*index +1+(1-ARRAY_START)] != -1  )
            PreOrderTraverse(piArray ,2*index +1+(1-ARRAY_START) );
    }
    
   
}

void DisplayArray(int *piArray , int iArraySize)
{
    for (int i=ARRAY_START ; i<=iArraySize -(1-ARRAY_START) ; ++ i)
    {
        printf("%d ", piArray[i]);
    }

    printf("\n");
}

// ������� ��������������
void LevelDisplay(int* piArray , int iArraySize)
{
    int j = 0 , k = 0;

    POSITION p;

    int iElem = -1; 

    int iDepth = GetBiTreeDepth(piArray ,iArraySize );

    for ( j =1 ; j <= iDepth ; ++ j)
    {
        printf("%d��,", j );

        // ��һ��2��0��
        // �ڶ���2��1��
        for (k=1; k<= (int)pow(2, j-1) ; ++k)
        {
            p.iLevel = j;
            p.iOrder = k;
            iElem = GetElem(piArray , p);
            if(iElem != -1)
                printf("%d  ",iElem);
        }

        printf("\n");
    }
}


// ����
//     piArray ����˵��
//     p  ɾ��Ԫ�صĸ���
//     bLeftOrRight��ɾ��������(0)�����Һ��� (1)
void DeleteChild( int *piArray , POSITION p, bool bLeftOrRight )
{
    queue<int> q;
    
    // �ҵ�Ҫɾ����λ��
    int i = (int)pow(2, p.iLevel -1 ) + p.iOrder - 1 - (1-ARRAY_START) ;

    if( piArray[i] == -1)
        return;

    i = i*2 + bLeftOrRight  + (1-ARRAY_START) ;

    do 
    {
        // i������
        if( piArray[2*i + (1-ARRAY_START)] != -1)
            q.push(2*i + (1-ARRAY_START));
        
        // i���Һ���
        if( piArray[2*i + 1 + (1-ARRAY_START)] != -1)
            q.push( 2*i + 1 + (1-ARRAY_START) );
        
        piArray[i]  = -1 ; // ��Ϊ��

        i = q.front();
        q.pop();

    } while (!q.empty());

}

// ����
//     piArray Ŀ������ĵ�ַ
//     iArray �������Ч��С
//     iElem Ҫ�����Ԫ��,�佫������
//     bLeftOrRight �ǵ������ӻ����Һ���
//     pInsert��Ҫ����������ַ, ��������
// ����:��
void InsertChild(int *piArray , int iArraySize ,int iElem , bool bLeftOrRight ,int *pInsert)
{
    int  k= 0 ;
        
    int i = ARRAY_START;

    while (i<=iArraySize)
    {
        if(piArray[i] == iElem)
            break;
        ++i;
    }

    // kΪp������Һ��ӵ����
    k = 2*i + bLeftOrRight + (1-ARRAY_START);

    // �Ѵ�piArray��k��㿪ʼ��������Ϊ��k������������ʼ������    
    // ע���������ڴ�
    if( piArray[k] != -1)
        Move( piArray ,k , piArray , 2*k+1 + (1-ARRAY_START));

    Move( pInsert , 0, piArray , k );
}

// ��q�ƶ���T
// ����:
//        q �ƶ�����ĵ�ַ
//        j ���ƶ�����q�е�λ��
//        T ��������ĵ�ַ
//        i �ڽ�������T�е�λ��
//����: ��
void Move (int *q , int j , int *T , int i)
{
    // ��������� �ͰѺ���Ҳ����ȥ
    if( q[2*j + (1-ARRAY_START) ] != -1)
        Move( q , 2*j + (1-ARRAY_START) , T , 2*i +(1-ARRAY_START));

    // ������Һ��� �Һ���Ҳ�ƶ���ȥ

    if( q[2*j + 1 + (1-ARRAY_START)] != -1)
        Move( q , 2*j + 1 + (1-ARRAY_START) , T , 2*i +1 +(1-ARRAY_START));

     T[i] = q[j];

     q[j] = -1;
}


// ����:
//       piArray ����ָ��
//       iArraySize �������Ч��С
//       iElem ĳ��Ԫ�ص�ֵ
// ����: ���ֵܵ�ֵ,û�����ֵܷ���-1
int GetRightSibling(int* piArray , int iArraySize , int iElem)
{
    if( piArray[ARRAY_START] == -1)
        return -1;
    
    int i = ARRAY_START;
    while (i<=iArraySize)
    {
        // �� ARRAY_START ��Ϊ��ʡȥ���ж�
        if(piArray[i]==iElem && (i + (1-ARRAY_START) )%2 == 0)
            return piArray[i+1];
        ++i;
    }
    return -1;
}

// ����:
//       piArray ����ָ��
//       iArraySize �������Ч��С
//       iElem ĳ��Ԫ�ص�ֵ
// ����: ���ֵܵ�ֵ,û�����ֵܷ���-1
int GetLeftSibling(int* piArray , int iArraySize , int iElem)
{
    if( piArray[ARRAY_START] == -1)
        return -1;
       
    int i = ARRAY_START;
    while (i<=iArraySize)
    {
        if(piArray[i]==iElem && (i + (1- ARRAY_START) )%2 == 1)
            return piArray[i-1];

        ++i;
    }
    return -1;
}

// ����:
//       piArray ����ָ��
//       iArraySize �������Ч��С
//       iElem ĳ��Ԫ�ص�ֵ
// ����: �Һ��ӵ�ֵ,û���Һ��ӷ���-1
int GetRightChild(int* piArray, int iArraySize ,int iElem)
{
    if(piArray[ARRAY_START] == -1)
        return -1;
    
    int i = ARRAY_START;
    //��ε��������ж��� i<(int)pow(2,BiTreeDepth(T))-1
    while (i<=iArraySize) 
    {
        if( piArray[i] == iElem )
           return piArray[2*i+1 + (1-ARRAY_START)];
       
        ++i;
    }
    
    return -1;
}


// ����:
//       piArray ����ָ��
//       iArraySize �������Ч��С
//       iElem ĳ��Ԫ�ص�ֵ
// ����: ���ӵ�ֵ,û�����ӷ���-1
int GetLeftChild(int* piArray, int iArraySize ,int iElem)
{

    if(piArray[ARRAY_START] == -1)
        return -1;
    
    int i = ARRAY_START;
    //��ε��������ж��� i<(int)pow(2,BiTreeDepth(T))-1
    while (i<=iArraySize) 
    {
        if( piArray[i] == iElem )
            return piArray[2*i+ (1-ARRAY_START)];
        ++i;
            
    }

    return -1;
}

// ����:
//       piArray ����ָ��
//       iElem ĳ��Ԫ�ص�ֵ
// ����: ���׵�ֵ,û�и��׷���-1
int GetParent(int* piArray ,int iArraySize , int iElem)
{
    // �������� ����     �������Ĳ���������Ҳ����
    if( piArray[ARRAY_START] == -1 || piArray[ARRAY_START] == iElem)
        return -1;

    int i = ARRAY_START;
    // ��ε���� i<(int)pow(2,BiTreeDepth(T))-1
    while (i <= iArraySize ) //���ﵱ���鿪ʼΪ0ʱҲ�е�С����
    {
        if(piArray[i] == iElem)
#ifdef ARRAY_START_ZERO
         return (piArray[(i+1)/2-1]);
#elif ARRAY_START_ONE
        return (piArray[i/2]);
#endif
            
        ++i;
    }

    return -1;
}
// ����:
//       piArray ����ָ��
//       p Ԫ���ڶ�������λ��
//       iAssignValueԪ�ص���ֵ
// ����: ��
void Assign(int *piArray , POSITION p , int iAssignValue)
{
#ifdef ARRAY_START_ZERO
    piArray[(int)pow(2,p.iLevel-1) + p.iOrder - 2] = iAssignValue;
#elif ARRAY_START_ONE
    piArray[(int)pow(2,p.iLevel-1) + p.iOrder -1 ] = iAssignValue;
#endif
}

// ����:
//       piArray ����ָ��
//       p Ԫ���ڶ�������λ��
// ����: Ԫ��ֵ
int GetElem(int *piArray , POSITION p)
{
#ifdef ARRAY_START_ZERO
    return piArray[(int)pow(2,p.iLevel-1) + p.iOrder - 2];
#elif ARRAY_START_ONE
    return piArray[(int)pow(2,p.iLevel-1) + p.iOrder -1 ];
#endif
}


// ����:
//       piArray ����ָ��
//       piElem ���صĶ������ĸ�
// ����: �Ƿ�ɹ� 
bool GetRoot( int* piArray , int* piElem)
{
    if( (piArray[ARRAY_START] != -1) )
    {
        (*piElem) = piArray[ARRAY_START];
        return true;
    }

    return false;
}

// ���ö��������й���ȵ����� ������ʲô�� ���ﲻ��д��ʽ

// ����: piArray����ָ��
//     : iArraySize ����Ĵ�С ��CreateBiTree�ķ���ֵ
// ����: �����ɶ����������
int GetBiTreeDepth(int *piArray , int iArraySize)
{
    int iDepth = 0;

    while (iArraySize >=(int)pow(2,iDepth) - 1) // ����Ԫ�ش�1��ʼ��ʱ�� ����=��Ҳû��ϵ
        ++ iDepth;                               // ��Ԫ�ش�0 ��ʼ �ͱ����=����

    return iDepth;
   
}

bool IsBiTreeEmpty(int *piArray)
{
    return (piArray[ARRAY_START] == -1);
}


void InitArray(int* piArray)
{
    for (unsigned int i = 0; i<ARRAY_SIZE ; ++i)
        piArray[i] = -1;
}

// �������������ĳ���
// �м�����ݾͲ�������-1 �����еĻ� ��ô���п���ĳһ���˫����-1 
int CreateBiTree( int *piArray)
{
    unsigned int index = ARRAY_START;

    FILE* fp = fopen("sequential storage.txt","r");

    while (true)
    {
        fscanf(fp," %d", &piArray[index]);

        if(piArray[index] == -1)
            break;

        // ��ε��������Խ���ж�  �Ҹо��ⲻ��Խ���жϰ�
        // ���ǹ涨����һ��Ӧ�����Һ���
        // ��ȥ��
//         if( 2*index + 1 >= ARRAY_SIZE )
//         {
//             printf("error>>more than array size.\n");
//             return ;
//         }

        // ��ǰ������ĸ���㲻��Ϊ�ս��

#ifdef ARRAY_START_ZERO
        if ( (index != 0)&& (piArray[(index +1 )/2 -1] == -1))
        {
            printf("error>>parent is null .\n");
            goto CLEAN;   
        }

        // �����ǰ�����������
#elif (ARRAY_START_ONE)
        if ( (index != 1)&& (piArray[index/2] == -1) )
        {
            printf("error>>parent is null .\n");
            goto CLEAN;
        }

#endif
        ++ index;
    }

CLEAN:
    fclose(fp);
    return (index - 1 );
}



