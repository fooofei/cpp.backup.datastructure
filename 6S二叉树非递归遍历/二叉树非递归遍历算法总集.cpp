//********************************************************************
//    二叉树非递归遍历算法总集.CPP    文件注释
//    FileName   :    二叉树非递归遍历算法总集.CPP
//    FilePath   :    
//    Author     :    
//    CreateTime :    2013/5/1 14:15
//    ModifyTime :    2013/5/15
//    Description:    重新整理思路 算是复习
// 
// 1. 递归遍历没有技术含量  这里的遍历 全是非递归的 
// 2. 需要用到的栈和队列 全是STL 不自己实现 因为这里主要温习算法
// 3. 英文:前序PreOrder 中序 infix order  后序 postorder
// 4. 遍历的理解1二叉树的输出是没有按照输入的次序的,为了有次序,就与 队列  栈 相结合,实现有序输出 
// 5. 非递归栈遍历 就是抛弃了 最传统的递归遍历二叉树的方法   方法改变了 
//				但是遍历的顺序还是原来的顺序 是不能被改变的
// 6. 后序遍历的难度是最大的 中序遍历的难度是最小的
// 7. 集百家之长 很多算法的哦 饕餮盛宴
// 8. 增加非递归不使用栈的方法(逆转链方法遍历二叉树http://blog.csdn.net/stund/article/details/7541829)
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
void PreOrderTraverse2(PBTNODE pRoot); // 推荐 与层序遍历类似 好记忆
void PreOrderTraverse3(PBTNODE pRoot); // 推荐 与下面的遍历算法类似 能成整体


void InOrderTraverse(PBTNODE pRoot);
void InOrderTraverse2(PBTNODE pRoot);
void InOrderTraverse3(PBTNODE pRoot); // 推荐
void InOrderTraverse4(PBTNODE pRoot); // Morris方法

void LevelOrderTraverse(PBTNODE pRoot);

void PosOrderTraverse(PBTNODE pRoot);
void PosOrderTraverse2(PBTNODE pRoot); // 推荐
void PosOrderTraverse3(PBTNODE pRoot);
void PosOrderTraverse4(PBTNODE pRoot);

void DestroyTree(PBTNODE &pRoot);

int GetBiTreeDepth(PBTNODE pRoot);

// 有bad  关键字的遍历方法 修改了二叉树的结构 那么我们不容易释放二叉树
//                       要释放二叉树就要保存每个结点的地址

// 对于下面几个有关键字bad 的算法,我在另一个文件中给出了其不bad的实现
//         就是修改了栈保存的数据类型,不再保存结点地址,而是保存结点全部

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




// Morris方法  (Robson方法 不要了 很复杂 而且 找到的还不对)
// 经典 不需要栈的空间  只需要一个临时的结点指针
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


// 递归创建树 更改为读文件 这样每次运行免去手动输入数据

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

 // 没有技术含量
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


// 前序遍历
// 用到的数据结构: 栈
// 步骤 1. 根入栈
//      2. 循环 栈不空
//         2.1 出栈 作为父结点
//         2.2 循环 当父结点不为空
//              2.2.1 输出父结点数据
//              2.2.2 右孩子入栈 不用管是否为NULL
//              2.2.3 父结点重新赋值指向左孩子
void PreOrderTraverse(PBTNODE pRoot)
{
	if(pRoot == NULL)
		return;

	stack<PBTNODE> s;
	// 根入栈
	s.push(pRoot);

	//循环 栈不空
	while(!s.empty())
	{
		// 出栈 作为父结点
		pRoot = s.top();
		s.pop();
	
		// 循环 当父结点不为空
		while(pRoot != NULL)
		{
			// 输出父结点数据
			printf("%c ",pRoot->Data);
			// 右孩子入栈 不用管是否为NULL
			s.push(pRoot->pRNext);
			// 父结点重新赋值指向左孩子
			pRoot = pRoot->pLNext;
		}
	}

	printf("\n");
}

// 前序遍历 2 (推荐  因为与层序遍历类似 好记忆)
// 用到的数据结构:栈
// 步骤 1. 根入栈
//      2. 循环栈不空
//         2.1. 取出数据 输出
//         2.2. 父结点有右孩子 右孩子入栈 其有左孩子 左孩子入栈


// 与层序遍历的结构很类似
void PreOrderTraverse2(PBTNODE pRoot)
{
	if(pRoot == NULL )
		return;

	stack<PBTNODE> s;
 // 根入栈
	s.push(pRoot);

	// 循环栈不空
	while(!s.empty())
	{
		// 出栈需要调用两个函数...Orz...
		// 取出数据 输出
		pRoot = s.top();
		s.pop();
		printf("%c ",pRoot->Data );

		// 其有右孩子 右孩子入栈 其有左孩子 左孩子入栈
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

// 相比之下 InOrderTraverse2 更简洁

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


// 推荐背过 
// 严蔚敏课本上有一个单个的中序遍历(注意 只有这一个方法)

// 用到的数据结构: 栈
// 步骤 1. 循环 父结点不为空 或者 栈不空
//          1.1 父结点不空 入栈 父结点指向左孩子
//          1.2 父结点为空   
//             1.2.1 取出结点作为新的父结点
//             1.2.2 输出数据
//             1.2.3 父结点指向右孩子 这时的父结点一定没有左孩子了 (为什么?因为这是中序遍历啊.)

void InOrderTraverse2(PBTNODE pRoot)
{
    // 开始无需判断 pRoot == NULL  注意到了没
    stack<PBTNODE> s;
    
    // 循环 父结点不为空 或者 栈不空
    while( pRoot != NULL || !s.empty() )
    {
        // 父结点不空 入栈 父结点指向左孩子 
         if( pRoot != NULL )
         {
               s.push(pRoot);
               pRoot = pRoot->pLNext;
         }
         // 父结点为空   
         else
         {
             // 取出结点作为新的父结点 
             pRoot = s.top();
             s.pop();

             // 输出数据
             printf("%c ",pRoot->Data );

             // 父结点指向右孩子 这时的父结点一定没有左孩子了
             pRoot = pRoot->pRNext;
         }
    }

	printf("\n");
}


// 推荐
// 应该看做是InOrderTraverse 的改进和简化
// 很神奇 跟InOrderTraverse2的结构是很相似的  但是 人家里面不是while循环
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


// bad 就是不推荐使用 很坏的方法
// 坏在哪里 调用之后 会改变二叉树的结构
// 这竟然是我自己想到的算法,好惊讶.原因是原来老师没给这个算法,所以就类比老师给的,想出来的

// 用到的数据结构:栈
// 步骤: 1. 根入栈
//       2. 栈不空 循环
//          2.1 出栈 另外的结点保存出栈结点的左孩子地址
//          2.2 无左孩子(即为空) 输出上步出栈的结点 
//          2.3 有左孩子 出栈结点的左孩子赋值为空
//               2.3.1 若有右孩子 右孩子入栈
//               2.3.2 2.1步出栈的结点入栈  将保存的左孩子地址入栈 
void InOrderTraverse_bad(PBTNODE pRoot)
{
	if(pRoot == NULL)
		return;

	stack<PBTNODE> s;

	PBTNODE pLNext = NULL ;
	// 根入栈
	s.push(pRoot);

	// 栈不空 循环
	while(!s.empty())
	{
		// 出栈 另外的结点保存出栈结点的左孩子地址
		pRoot = s.top();
		s.pop();
		pLNext = pRoot->pLNext;


		// 无左孩子(即为空) 输出上步出栈的结点 
		if(pLNext == NULL)
			printf("%c ",pRoot->Data );

		// 有左孩子 出栈结点的左孩子赋值为空
		else
		{
			pRoot->pLNext = NULL;
			// 若有右孩子 右孩子入栈
			if(pRoot->pRNext != NULL )
				s.push(pRoot->pRNext );

			// 出栈的结点入栈  将保存的左孩子地址入栈 
			s.push(pRoot);
			s.push(pLNext);
		}
	}

	printf("\n");
}

// 2012-9-3 晚在网上一份论文找到的最新的算法  是东南大学的 论文在目录下
// 文件为:"新型二叉树后序遍历非递归算法.pdf"
// 
// 后序遍历要求前序遍历要熟悉 ,因为此算法的思想是前序遍历的反序

// 用到的数据结构:栈
// 步骤 1. 定义两个栈(主栈和辅助栈) 根入主栈
//      2. 循环 主栈不空
//         2.1 出主栈 作为父结点
//         2.2 循环 当父结点不为空
//              2.2.1 将父结点压入辅助栈
//              2.2.2 左孩子入主栈 不用管是否为NULL
//              2.2.3 父结点重新赋值指向右孩子
void PosOrderTraverse(PBTNODE pRoot)
{
    if( pRoot == NULL )
        return ;

    stack<PBTNODE> s;
    stack<PBTNODE> sLRM; // 辅助栈

    s.push( pRoot );

    while(! s.empty() )
    {
        pRoot = s.top();
        s.pop();

        while( pRoot != NULL )// 此方法来自一份报纸  反序思想
        {
            // printf("%c ", pRoot->Data );
               
            // 本来是前序遍历的输出数据 我们不输出 放到另一个栈中去
            sLRM.push( pRoot );

            // 下面的 入栈左孩子 父结点指向右孩子与前序遍历也不同了
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


// 我推荐
// 于是我将上边的 PosOrderTraverse 更改为容易理解的方式了


// 用到的数据结构:栈
// 步骤 1. 定义两个栈(主栈和辅助栈) 根入主栈
//      2. 循环 主栈不空
//         2.1. 取出主栈数据 放入辅助栈
//         2.2. 父结点有左孩子 左孩子入主栈 其有右孩子 左孩子入主栈

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

// 另外一种方法  在栈中放入空指针来区别 是从左孩子移动到根节点还是从右孩子移动的根节点
// 无标记变量
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

// 用一个标记标记右子树是否访问过 浪费空间
// 标志数组的大小也是需要依据树的大小更改的
// 算法比较复杂  不推荐 

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

// bad 就是不推荐使用 很坏的方法
// 坏在哪里 调用之后 会改变二叉树的结构

// 用到的数据结构:栈
// 步骤: 1. 根入栈
//       2. 循环栈不空
//          2.1 出栈 作为父结点
//          2.2 判断无左右孩子 输出数据
//          2.3 有任意一个孩子
//              2.3.1 保存其 左右孩子的地址  并且将父结点的左右孩子指针赋值为空
//              2.3.2 将父结点入栈
//              2.3.3 若有 右孩子  右孩子入栈   若有左孩子  左孩子 入栈
void PosOrderTraverse_bad(PBTNODE pRoot)
{

	if(pRoot == NULL )
		return ;

	PBTNODE pLNext = NULL , pRNext = NULL;

	stack<PBTNODE> s;
	// 根入栈
	s.push(pRoot);

	// 循环 栈不空
	while (!s.empty())
	{
		// 出栈
		pRoot = s.top();
		s.pop();

		// 当无 左右孩子时   输出数据
		if(pRoot->pLNext == NULL && pRoot->pRNext == NULL)
			printf("%c ",pRoot->Data );

		// 若有任意一个孩子
		else
		{
			// 保存其 左右孩子的地址  并且将父结点的左右孩子指针赋值为空
			pLNext = pRoot->pLNext;
			pRoot->pLNext = NULL;
			
			
			pRNext = pRoot->pRNext;
			pRoot->pRNext = NULL;
			

			// 将父结点入栈
			s.push(pRoot);

			// 若有 右孩子  右孩子入栈   若有左孩子  左孩子 入栈   
			if(pRNext != NULL)
				s.push(pRNext);

			if(pLNext != NULL)
				s.push(pLNext);
		}
		
	}

	printf("\n");
}



// 层序遍历用到的数据结构:队列
// 步骤 1. 根入队
//      2. 循环队列不空
//          2.1. 取出数据 输出
//          2.2. 有左孩子 左孩子入队 有右孩子 右孩子入队

void LevelOrderTraverse(PBTNODE pRoot)
{
	if(pRoot == NULL)
		return;

	queue<PBTNODE> q;
  // 根入队
	q.push(pRoot);

	// 循环队列不空
	while (!q.empty())
	{
		// 取出数据 输出
		pRoot = q.front();
		q.pop();
		printf("%c ",pRoot->Data );
		
		// 有左孩子 左孩子入队 有右孩子 右孩子入队
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