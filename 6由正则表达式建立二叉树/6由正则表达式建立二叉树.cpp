#include <stdio.h>
#include <malloc.h>

#define   MaxSize    20
typedef   char    ElemType;

typedef struct node 
{
    ElemType       data;                /*数据元素*/
    struct node    *lchild;        /*指向左孩子*/
    struct node    *rchild;        /*指向右孩子*/
} BTNode;


typedef  struct
{
    BTNode    *data[MaxSize];
    int       top;              //栈顶指针
} SqStack1;


typedef  struct
{
    ElemType  data[MaxSize];
    int       top;              //栈顶指针
} SqStack2;

SqStack1   szz;
SqStack2   zmz;

void CLeafNode(BTNode *&T,char ch);
void CSubTree(BTNode *&T,char c);

void CreatBTNode(BTNode *&T,char *exp)
{
    zmz.top=-1;      //初始化栈顶
    szz.top=-1;
    T=NULL;
    while(*exp!='\0')
    {
        switch(*exp)
        {
        case '(':                /*判定为左括号*/
            zmz.top++;
            zmz.data[zmz.top]=*exp;
            exp++;                /*继续扫描其他字符*/
            break;
        case ')':                /*判定为右括号*/
                while(zmz.data[zmz.top]!='(')
                {
                    CSubTree(T,zmz.data[zmz.top]);
                    zmz.top--;    
                }
                zmz.top--;     /*将(退栈*/
                exp++;         /*继续扫描其他字符*/
                break;
        case '+':                /*判定为加或减号*/
        case '-':
            while (zmz.data[zmz.top]=='*' || zmz.data[zmz.top]=='/')
            {   /*将栈中'*'或'/'运算符依次出栈并存放到postexp中*/
                CSubTree(T,zmz.data[zmz.top]);    //建二叉子树并入栈
                zmz.top--;
            }
            zmz.top++;
            zmz.data[zmz.top]=*exp; /*将'+'或'-'进栈*/
            exp++;                /*继续扫描其他字符*/
            break;
        case '*':                /*判定为'*'或'/'号*/
        case '/':
            while (zmz.data[zmz.top]=='*' || zmz.data[zmz.top]=='/')
            {   /*将栈中'*'或'/'运算符依次出栈并存放到postexp中*/
                CSubTree(T,zmz.data[zmz.top]);    //建二叉子树并入栈
                zmz.top--;
            }
            zmz.top++;
            zmz.data[zmz.top]=*exp; /*将'*'或'/'进栈*/
            exp++;                /*继续扫描其他字符*/
            break;
        case ' ':break;            /*过滤掉空格*/
        default:                /*处理数字字符*/
                if(*exp>='0' && *exp<='9') /*判定为数字*/    
                    CLeafNode(T,*exp);   //建立叶子结点
                while (zmz.data[zmz.top]=='*' || zmz.data[zmz.top]=='/')
                {    /*将栈中'*'或'/'运算符依次出栈并存放到postexp中*/
                    CSubTree(T,zmz.data[zmz.top]);    //建二叉子树并入栈
                    zmz.top--;
                }
                exp++;
                break;
        }
    }//while
    while(zmz.top!=-1)
    {
        CSubTree(T,zmz.data[zmz.top]);    //建二叉子树并入栈
            zmz.top--;
    }
}


/**********************建立叶子结点**************************/

void CLeafNode(BTNode *&T,char ch)
{
    T=(BTNode *)malloc(sizeof(BTNode));
    T->data=ch;
    T->lchild=T->rchild=NULL;
    szz.top++;
    szz.data[szz.top]=T;   //将叶子结点指针入栈
}

/**********************建立子树**************************/

void CSubTree(BTNode *&T,char c)
{
    T=(BTNode *)malloc(sizeof(BTNode));
    T->data=c;
    T->rchild=szz.data[szz.top];
    szz.top--;
    T->lchild=szz.data[szz.top];
    szz.data[szz.top]=T;  //将子树的根结点进栈 
}


/**********************输出二叉树**************************/

void DispBTNode(BTNode *b)    /*以括号表示法(广义表)输出二叉树*/
{
    if (b!=NULL)
    {
        printf("%c",b->data);
        if(b->lchild!=NULL || b->rchild!=NULL)
        {
            printf("(");
            DispBTNode(b->lchild);
            if(b->rchild!=NULL) 
                printf(",");
            DispBTNode(b->rchild);
            printf(")");
        }
    }
} //DispBTNode


void main()
{
    char string[20];
    BTNode  *b;
    printf("请输入一个四则运算表达式：");
    gets(string);
    CreatBTNode(b,string);
    printf("生成的二叉树为：");
    DispBTNode(b);
    printf("\n");
    return ;
}