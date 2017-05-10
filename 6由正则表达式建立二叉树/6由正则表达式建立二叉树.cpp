#include <stdio.h>
#include <malloc.h>

#define   MaxSize    20
typedef   char    ElemType;

typedef struct node 
{
    ElemType       data;                /*����Ԫ��*/
    struct node    *lchild;        /*ָ������*/
    struct node    *rchild;        /*ָ���Һ���*/
} BTNode;


typedef  struct
{
    BTNode    *data[MaxSize];
    int       top;              //ջ��ָ��
} SqStack1;


typedef  struct
{
    ElemType  data[MaxSize];
    int       top;              //ջ��ָ��
} SqStack2;

SqStack1   szz;
SqStack2   zmz;

void CLeafNode(BTNode *&T,char ch);
void CSubTree(BTNode *&T,char c);

void CreatBTNode(BTNode *&T,char *exp)
{
    zmz.top=-1;      //��ʼ��ջ��
    szz.top=-1;
    T=NULL;
    while(*exp!='\0')
    {
        switch(*exp)
        {
        case '(':                /*�ж�Ϊ������*/
            zmz.top++;
            zmz.data[zmz.top]=*exp;
            exp++;                /*����ɨ�������ַ�*/
            break;
        case ')':                /*�ж�Ϊ������*/
                while(zmz.data[zmz.top]!='(')
                {
                    CSubTree(T,zmz.data[zmz.top]);
                    zmz.top--;    
                }
                zmz.top--;     /*��(��ջ*/
                exp++;         /*����ɨ�������ַ�*/
                break;
        case '+':                /*�ж�Ϊ�ӻ����*/
        case '-':
            while (zmz.data[zmz.top]=='*' || zmz.data[zmz.top]=='/')
            {   /*��ջ��'*'��'/'��������γ�ջ����ŵ�postexp��*/
                CSubTree(T,zmz.data[zmz.top]);    //��������������ջ
                zmz.top--;
            }
            zmz.top++;
            zmz.data[zmz.top]=*exp; /*��'+'��'-'��ջ*/
            exp++;                /*����ɨ�������ַ�*/
            break;
        case '*':                /*�ж�Ϊ'*'��'/'��*/
        case '/':
            while (zmz.data[zmz.top]=='*' || zmz.data[zmz.top]=='/')
            {   /*��ջ��'*'��'/'��������γ�ջ����ŵ�postexp��*/
                CSubTree(T,zmz.data[zmz.top]);    //��������������ջ
                zmz.top--;
            }
            zmz.top++;
            zmz.data[zmz.top]=*exp; /*��'*'��'/'��ջ*/
            exp++;                /*����ɨ�������ַ�*/
            break;
        case ' ':break;            /*���˵��ո�*/
        default:                /*���������ַ�*/
                if(*exp>='0' && *exp<='9') /*�ж�Ϊ����*/    
                    CLeafNode(T,*exp);   //����Ҷ�ӽ��
                while (zmz.data[zmz.top]=='*' || zmz.data[zmz.top]=='/')
                {    /*��ջ��'*'��'/'��������γ�ջ����ŵ�postexp��*/
                    CSubTree(T,zmz.data[zmz.top]);    //��������������ջ
                    zmz.top--;
                }
                exp++;
                break;
        }
    }//while
    while(zmz.top!=-1)
    {
        CSubTree(T,zmz.data[zmz.top]);    //��������������ջ
            zmz.top--;
    }
}


/**********************����Ҷ�ӽ��**************************/

void CLeafNode(BTNode *&T,char ch)
{
    T=(BTNode *)malloc(sizeof(BTNode));
    T->data=ch;
    T->lchild=T->rchild=NULL;
    szz.top++;
    szz.data[szz.top]=T;   //��Ҷ�ӽ��ָ����ջ
}

/**********************��������**************************/

void CSubTree(BTNode *&T,char c)
{
    T=(BTNode *)malloc(sizeof(BTNode));
    T->data=c;
    T->rchild=szz.data[szz.top];
    szz.top--;
    T->lchild=szz.data[szz.top];
    szz.data[szz.top]=T;  //�������ĸ�����ջ 
}


/**********************���������**************************/

void DispBTNode(BTNode *b)    /*�����ű�ʾ��(�����)���������*/
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
    printf("������һ������������ʽ��");
    gets(string);
    CreatBTNode(b,string);
    printf("���ɵĶ�����Ϊ��");
    DispBTNode(b);
    printf("\n");
    return ;
}