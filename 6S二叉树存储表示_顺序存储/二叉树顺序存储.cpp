//********************************************************************
//    二叉树顺序存储.CPP    文件注释
//    FileName   :    二叉树顺序存储.CPP
//    FilePath   :    
//    Author     :    
//    CreateTime :    2013/5/3 20:09
//    Description:    重写 删去以前的代码  算作是代码重构
// 1.-1 为结束符 为空
// 2.由原来的数组0 开始 变为现在的从数组元素1 开始
// 3.顺序存储一般只用于完全二叉树
// 4.在一个从0 开始的数组中  每一个的双亲就是 (i+1)/2-1 
// 5.从0开始的数组中每一项的左孩子就是 2*i+1  右孩子就是2*i+2
// 6.本程序有个最大的错误 就是MAX 定义的值小的时候 就很容易遇到有的
//      节点没有孩子 可是我们还一如既往在判断有没有孩子 于是数组就越界
// 7.当在代码中遇到 1- ARRAY_START的时候 省去不看 这是我为了兼顾数组从0 
//       和从1开始两种情况而写的
// 8.共21个函数
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

const unsigned int  ARRAY_SIZE  =  100  ;  // 构造成二叉树数组的大小

// 两个宏 只能选一个
//#define  ARRAY_START_ZERO  0// 数组从0 开始
#define  ARRAY_START_ONE  1// 数组从1 开始


#ifdef ARRAY_START_ZERO
    #define ARRAY_START ARRAY_START_ZERO
#endif
#ifdef ARRAY_START_ONE
    #define ARRAY_START ARRAY_START_ONE
#endif



// 初始化数组全部为-1
void InitArray(int* piArray);
// 返回输入的数组的长度
int CreateBiTree( int *piArray);
// 树空返回true   不空返回false
bool IsBiTreeEmpty(int *piArray);

// 参数: piArray数组指针
//     : iArraySize 数组的大小 是CreateBiTree的返回值
// 返回: 所构成二叉树的深度
int GetBiTreeDepth(int *piArray , int iArraySize);

// 参数:
//       piArray 数组指针
//       iElem 返回的二叉树的根
// 返回: 是否成功 
bool GetRoot( int* piArray , int* piElem);

// 参数:
//       piArray 数组指针
//       p 元素在二叉树的位置
// 返回: 元素值
int GetElem(int *piArray , POSITION p);

// 参数:
//       piArray 数组指针
//       p 元素在二叉树的位置
//       iAssignValue元素的新值
// 返回: 无
void Assign(int *piArray , POSITION p , int iAssignValue);

// 参数:
//       piArray 数组指针
//       iArraySize 数组的有效大小
//       iElem 某个元素的值
// 返回: 父亲的值,没有父亲返回-1
int GetParent(int* piArray ,int iArraySize , int iElem);

// 参数:
//       piArray 数组指针
//       iArraySize 数组的有效大小
//       iElem 某个元素的值
// 返回: 左孩子的值,没有左孩子返回-1
int GetLeftChild(int* piArray, int iArraySize ,int iElem);

// 参数:
//       piArray 数组指针
//       iArraySize 数组的有效大小
//       iElem 某个元素的值
// 返回: 右孩子的值,没有右孩子返回-1
int GetRightChild(int* piArray, int iArraySize ,int iElem);

// 参数:
//       piArray 数组指针
//       iArraySize 数组的有效大小
//       iElem 某个元素的值
// 返回: 左兄弟的值,没有左兄弟返回-1
int GetLeftSibling(int* piArray , int iArraySize , int iElem);

// 参数:
//       piArray 数组指针
//       iArraySize 数组的有效大小
//       iElem 某个元素的值
// 返回: 右兄弟的值,没有右兄弟返回-1
int GetRightSibling(int* piArray , int iArraySize , int iElem);

// 把q移动到T
// 参数:
//        q 移动数组的地址
//        j 在移动数组q中的位置
//        T 接收数组的地址
//        i 在接收数组T中的位置
//返回: 无
void Move (int *q , int j , int *T , int i);

// 参数
//     piArray 目的数组的地址
//     iArray 数组的有效大小
//     iElem 要插入的元素,其将做父亲
//     bLeftOrRight 是当做左孩子(0)还是右孩子 (1)
//     pInsert需要插入的数组地址, 这是祖先
// 返回:无
void InsertChild(int *piArray ,int iArraySize, int iElem , bool bLeftOrRight ,int *pInsert);

// 参数
//     piArray 不用说了
//     p  删除元素的父亲
//     bLeftOrRight是删除其左孩子(0)还是右孩子 (1)

void DeleteChild( int *piArray , POSITION p, bool bLeftOrRight );


// 下面都是打印方法 

// 层序输出 但不是依靠队列
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
    printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",IsBiTreeEmpty(iArray),
        GetBiTreeDepth(iArray , iArraySize));

    int iElem;

    bool bOk = GetRoot(iArray , &iElem );

    if(bOk)
        printf("二叉树的根为:%d.\n",iElem);
    else
        printf("二叉树是空的,没有根.\n");

    printf("层序遍历二叉树:");
    LevelOrderTraverse(iArray );

    printf("前序遍历二叉树:");
    PreOrderTraverse( iArray , ARRAY_START );
    printf("\n");

    printf("中序遍历二叉树:");
    InOrderTraverse( iArray , ARRAY_START );
    printf("\n");

    printf("后序遍历二叉树:");
    PosOrderTraverse( iArray , ARRAY_START );
    printf("\n");

    POSITION p;
    p.iLevel = 3;
    p.iOrder = 2;

    if( p.iOrder > (int)pow(2 , p.iLevel-1))
        exit(0);

    printf("第%d层,第%d个为%d.--修改为-->110.\n",p.iLevel , p.iOrder , GetElem(iArray,p));
  
    Assign(iArray , p ,110 );

    printf("第%d层,第%d个为%d.\n",p.iLevel , p.iOrder , GetElem(iArray,p));

    
    iElem = 110;

    printf("结点%d的双亲为%d,左孩子为%d,右孩子为%d,左兄弟为%d,右兄弟为%d.\n" , iElem ,
        GetParent(iArray ,iArraySize , iElem),
        GetLeftChild( iArray , iArraySize , iElem),
        GetRightChild(iArray ,iArraySize , iElem ),
        GetLeftSibling(iArray , iArraySize , iElem ),
        GetRightSibling(iArray , iArraySize ,iElem ));
    
    printf("输出数组:");
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

// 层序输出 但不是依靠队列
void LevelDisplay(int* piArray , int iArraySize)
{
    int j = 0 , k = 0;

    POSITION p;

    int iElem = -1; 

    int iDepth = GetBiTreeDepth(piArray ,iArraySize );

    for ( j =1 ; j <= iDepth ; ++ j)
    {
        printf("%d层,", j );

        // 第一层2的0次
        // 第二层2的1次
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


// 参数
//     piArray 不用说了
//     p  删除元素的父亲
//     bLeftOrRight是删除其左孩子(0)还是右孩子 (1)
void DeleteChild( int *piArray , POSITION p, bool bLeftOrRight )
{
    queue<int> q;
    
    // 找到要删除的位置
    int i = (int)pow(2, p.iLevel -1 ) + p.iOrder - 1 - (1-ARRAY_START) ;

    if( piArray[i] == -1)
        return;

    i = i*2 + bLeftOrRight  + (1-ARRAY_START) ;

    do 
    {
        // i有左孩子
        if( piArray[2*i + (1-ARRAY_START)] != -1)
            q.push(2*i + (1-ARRAY_START));
        
        // i有右孩子
        if( piArray[2*i + 1 + (1-ARRAY_START)] != -1)
            q.push( 2*i + 1 + (1-ARRAY_START) );
        
        piArray[i]  = -1 ; // 置为空

        i = q.front();
        q.pop();

    } while (!q.empty());

}

// 参数
//     piArray 目的数组的地址
//     iArray 数组的有效大小
//     iElem 要插入的元素,其将做父亲
//     bLeftOrRight 是当做左孩子还是右孩子
//     pInsert需要插入的数组地址, 这是祖先
// 返回:无
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

    // k为p的左或右孩子的序号
    k = 2*i + bLeftOrRight + (1-ARRAY_START);

    // 把从piArray的k结点开始的子树移为从k结点的右子树开始的子树    
    // 注意是线性内存
    if( piArray[k] != -1)
        Move( piArray ,k , piArray , 2*k+1 + (1-ARRAY_START));

    Move( pInsert , 0, piArray , k );
}

// 把q移动到T
// 参数:
//        q 移动数组的地址
//        j 在移动数组q中的位置
//        T 接收数组的地址
//        i 在接收数组T中的位置
//返回: 无
void Move (int *q , int j , int *T , int i)
{
    // 如果有左孩子 就把孩子也动过去
    if( q[2*j + (1-ARRAY_START) ] != -1)
        Move( q , 2*j + (1-ARRAY_START) , T , 2*i +(1-ARRAY_START));

    // 如果有右孩子 右孩子也移动过去

    if( q[2*j + 1 + (1-ARRAY_START)] != -1)
        Move( q , 2*j + 1 + (1-ARRAY_START) , T , 2*i +1 +(1-ARRAY_START));

     T[i] = q[j];

     q[j] = -1;
}


// 参数:
//       piArray 数组指针
//       iArraySize 数组的有效大小
//       iElem 某个元素的值
// 返回: 右兄弟的值,没有右兄弟返回-1
int GetRightSibling(int* piArray , int iArraySize , int iElem)
{
    if( piArray[ARRAY_START] == -1)
        return -1;
    
    int i = ARRAY_START;
    while (i<=iArraySize)
    {
        // 加 ARRAY_START 是为了省去宏判断
        if(piArray[i]==iElem && (i + (1-ARRAY_START) )%2 == 0)
            return piArray[i+1];
        ++i;
    }
    return -1;
}

// 参数:
//       piArray 数组指针
//       iArraySize 数组的有效大小
//       iElem 某个元素的值
// 返回: 左兄弟的值,没有左兄弟返回-1
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

// 参数:
//       piArray 数组指针
//       iArraySize 数组的有效大小
//       iElem 某个元素的值
// 返回: 右孩子的值,没有右孩子返回-1
int GetRightChild(int* piArray, int iArraySize ,int iElem)
{
    if(piArray[ARRAY_START] == -1)
        return -1;
    
    int i = ARRAY_START;
    //严蔚敏这里的判断是 i<(int)pow(2,BiTreeDepth(T))-1
    while (i<=iArraySize) 
    {
        if( piArray[i] == iElem )
           return piArray[2*i+1 + (1-ARRAY_START)];
       
        ++i;
    }
    
    return -1;
}


// 参数:
//       piArray 数组指针
//       iArraySize 数组的有效大小
//       iElem 某个元素的值
// 返回: 左孩子的值,没有左孩子返回-1
int GetLeftChild(int* piArray, int iArraySize ,int iElem)
{

    if(piArray[ARRAY_START] == -1)
        return -1;
    
    int i = ARRAY_START;
    //严蔚敏这里的判断是 i<(int)pow(2,BiTreeDepth(T))-1
    while (i<=iArraySize) 
    {
        if( piArray[i] == iElem )
            return piArray[2*i+ (1-ARRAY_START)];
        ++i;
            
    }

    return -1;
}

// 参数:
//       piArray 数组指针
//       iElem 某个元素的值
// 返回: 父亲的值,没有父亲返回-1
int GetParent(int* piArray ,int iArraySize , int iElem)
{
    // 二叉树空 不对     传进来的参数是树根也不对
    if( piArray[ARRAY_START] == -1 || piArray[ARRAY_START] == iElem)
        return -1;

    int i = ARRAY_START;
    // 严蔚敏是 i<(int)pow(2,BiTreeDepth(T))-1
    while (i <= iArraySize ) //这里当数组开始为0时也有点小问题
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
// 参数:
//       piArray 数组指针
//       p 元素在二叉树的位置
//       iAssignValue元素的新值
// 返回: 无
void Assign(int *piArray , POSITION p , int iAssignValue)
{
#ifdef ARRAY_START_ZERO
    piArray[(int)pow(2,p.iLevel-1) + p.iOrder - 2] = iAssignValue;
#elif ARRAY_START_ONE
    piArray[(int)pow(2,p.iLevel-1) + p.iOrder -1 ] = iAssignValue;
#endif
}

// 参数:
//       piArray 数组指针
//       p 元素在二叉树的位置
// 返回: 元素值
int GetElem(int *piArray , POSITION p)
{
#ifdef ARRAY_START_ZERO
    return piArray[(int)pow(2,p.iLevel-1) + p.iOrder - 2];
#elif ARRAY_START_ONE
    return piArray[(int)pow(2,p.iLevel-1) + p.iOrder -1 ];
#endif
}


// 参数:
//       piArray 数组指针
//       piElem 返回的二叉树的根
// 返回: 是否成功 
bool GetRoot( int* piArray , int* piElem)
{
    if( (piArray[ARRAY_START] != -1) )
    {
        (*piElem) = piArray[ARRAY_START];
        return true;
    }

    return false;
}

// 利用二叉树的有关深度的性质 性质是什么呢 这里不能写公式

// 参数: piArray数组指针
//     : iArraySize 数组的大小 是CreateBiTree的返回值
// 返回: 所构成二叉树的深度
int GetBiTreeDepth(int *piArray , int iArraySize)
{
    int iDepth = 0;

    while (iArraySize >=(int)pow(2,iDepth) - 1) // 当首元素从1开始的时候 不加=号也没关系
        ++ iDepth;                               // 首元素从0 开始 就必须加=号了

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

// 返回输入的数组的长度
// 中间的数据就不可能有-1 假如有的话 那么就有可能某一项的双亲是-1 
int CreateBiTree( int *piArray)
{
    unsigned int index = ARRAY_START;

    FILE* fp = fopen("sequential storage.txt","r");

    while (true)
    {
        fscanf(fp," %d", &piArray[index]);

        if(piArray[index] == -1)
            break;

        // 严蔚敏的数组越界判断  我感觉这不是越界判断啊
        // 而是规定了它一定应该有右孩子
        // 先去掉
//         if( 2*index + 1 >= ARRAY_SIZE )
//         {
//             printf("error>>more than array size.\n");
//             return ;
//         }

        // 当前数组结点的父结点不能为空结点

#ifdef ARRAY_START_ZERO
        if ( (index != 0)&& (piArray[(index +1 )/2 -1] == -1))
        {
            printf("error>>parent is null .\n");
            goto CLEAN;   
        }

        // 我们是按照这样做的
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



