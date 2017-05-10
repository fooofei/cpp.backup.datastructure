#include "LineStack.h"

// ��׺���ʽ����׺���ʽ��ת��
// 
// Converting infix expression to a postfix expression

// ��׺��Ϊ��׺ �ͺܷ����� 
// �����㲻������� 

// ����ջ ��׺���׺�� �㷨��  ������ɨ����׺���ʽ 
// 1.���������ǲ����� ֱ�����
// 2.��������������� (1)��������� ( ֱ����ջ (2) ���� ) ��ջ�������( ǰ�������������ջ�����
//			(3)�����ŵ������ ��ջ��������뵱ǰ��������Ƚ� ������  ����ջ 
//				����ջ��Ԫ�س�ջ�����
char Precede(char a ,char b);
bool IsOperator(char a);
int Calculate(int a , int b , char c);
int main ()
{
	LineStack<char> ObjTR;
	LineStack<char> PostFixFormal;
	LineStack<char> PostFix;
	ObjTR.InitStack();
	PostFixFormal.InitStack();
	PostFix.InitStack();
	printf("��������ʽ(��֧����λ��)\n");
	//3*(4+2)/2-5

	// /n * 
	ObjTR.Push('\n');
	char x = 0;
	char a = getchar();
	printf("��׺���ʽת��Ϊ��׺���ʽΪ��\n");
	//
	// �����ұ�����׺���ʽ��ÿ�����ֺͷ��ţ��������־������Ϊ��׺
	// ���ʽ��һ���֣����Ƿ��ţ����ж�����ջ�����ŵ����ȼ�����������
	// �����ȼ�����ջ�����ţ���ջ��Ԫ�����β������������ǰ���Ž�ջ
	// һֱ�����������׺���ʽΪֹ
	while(a!='\n'&&!ObjTR.IsEmpty())	//ת������
	{
		if(!IsOperator(a))	//	����
		{
			printf("%d ",atoi(&a));
			PostFixFormal.Push(a);
		}
		else			// ������
		{
			if (a=='(')
			{
				ObjTR.Push(a);
			}
			else if (a==')')
			{
				x = ObjTR.Pop();
				while (x!='(')
				{
					printf("%c ",x);
					PostFixFormal.Push(x);
					x = ObjTR.Pop();
				}
			}
			else
			{
				while ((Precede(ObjTR.GetTop(),a)=='>')||
					(Precede(ObjTR.GetTop(),a)=='='))
					{
						x = ObjTR.Pop();
						printf("%c ",x);
						PostFixFormal.Push(x);
					}

					ObjTR.Push(a);
			}
		}
		a = getchar();
	}

	while(!ObjTR.IsEmpty() && (x = ObjTR.Pop())!='\n')
	{
		printf("%c ",x);
		PostFixFormal.Push(x);
	}

	ObjTR.FreeStack();

	while (!PostFixFormal.IsEmpty())  // ��˳����ת��һ��
	{ 
		PostFix.Push(PostFixFormal.Pop());
	}

	PostFixFormal.FreeStack();		// ���� PostFix ������˳����� ������˳��

	LineStack<int> ObjND;
	ObjND.InitStack();

	while (!PostFix.IsEmpty())
	{
		x = PostFix.Pop();

		if (!IsOperator(x))
		{
			ObjND.Push(atoi(&x));
		}
		else
		{
			ObjND.Push(Calculate(ObjND.Pop(),ObjND.Pop(),x)); // ���������ע������˳��
		}													// �����ұߵ�Pop���ȿ�ʼ
	}


	printf("\n���ý��Ϊ%d \n",ObjND.Pop());

	while (!ObjND.IsEmpty())
	{
		printf("Left %d ",ObjND.Pop());
	}
	PostFix.FreeStack();
	ObjND.FreeStack();

	return 0;	
}

bool IsOperator(char a) 
{
	switch (a)
	{
	case '+':
	case '-':
	case '/':
	case '*':
	case '\n':
	case '(':
	case ')':
		
			return true;

	default :
		{
			return false;
		}
	}

}
char Precede(char a ,char b)//2012-6-27 ����д    ��->�� ) * / + -  (  \n   2012-9-2 ����д
{
	switch (b)				// Ӧ����( �����㼶��� ��Ϊ������������ʱ�����Ǿ�Ҫ��������ŵ� + - * / ����������ջ Ҫ��ջ �������� 
	{						// �����ŵ������ ��ջ��������뵱ǰ��������Ƚ� ������  ����ջ 
	case '+':
		{
			if(a==')'||a=='*'||a=='/')
			{
				return '>';
			}
			else if(a=='+')
			{
				return '=';
			}
			else//'-'  '\n'
			{
				return '<';
			}
			
		}
	case '-':if (a=='\n'||a=='(')
			 {
				 return '<';
			 }
			 else if (a=='-')
			 {
				 return '=';
			 }
			 else
			 {
				 return '>';
			 }
			

			
	case '*':
		{
			if(a==')')
			{
				return '>';
			}
			else if(a=='*')
			{
				return '=';
			}

			else
			{
				return '<';
			}
		}
	case '/':
		{
			if(a=='*'||a==')')
			{
				return '>';	
			}
			else if(a=='/')
			{
				return '=';
			}
			else
			{
				return '<';
			}
		}
	case '(':
		{
			if(a=='(')
			{
				return '=';
			}
			else if (a=='\n')
			{
				return '<';
			}
			else
			{
				return '>';
			}
			
		}
	case ')':
		{
			
			if(a==')')
			{
				return '=';
			}
			else
			{
				return '<';
			}
		
		}
	case '\n':
		{
			if(a=='\n')
			{
				return '=';
			}

			else
			{

				return '>';
			}
			
		}
	}
}


int Calculate(int a , int b , char c)
{
	switch(c)
	{
	case '+':
		{
			return a+b;
		}
	case '-':
		{
			return a-b;
		}
	case '*':
		{
			return a*b;
		}
	case '/':
		{
			return (a/b);
		}
	default:
		printf("operator not supported!\n");
		 
	}
}