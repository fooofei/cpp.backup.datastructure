#include "LineStack.h"

// 中缀表达式到后缀表达式的转换
// 
// Converting infix expression to a postfix expression

// 中缀变为后缀 就很方便了 
// 括号算不算运算符 

// 利用栈 中缀变后缀的 算法是  从左到右扫描中缀表达式 
// 1.若读到的是操作数 直接输出
// 2.若读到的是运算符 (1)该运算符是 ( 直接入栈 (2) 若是 ) 将栈中最近的( 前的所有运算符出栈、输出
//			(3)非括号的运算符 则栈顶运算符与当前运算符做比较 若低于  则入栈 
//				否则栈顶元素出栈、输出
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
	printf("请输入表达式(不支持两位数)\n");
	//3*(4+2)/2-5

	// /n * 
	ObjTR.Push('\n');
	char x = 0;
	char a = getchar();
	printf("中缀表达式转换为后缀表达式为：\n");
	//
	// 从左到右遍历中缀表达式的每个数字和符号，若是数字就输出成为后缀
	// 表达式的一部分，若是符号，则判断其与栈顶符号的优先级，是右括号
	// 或优先级低于栈顶符号，则栈顶元素依次并输出，并将当前符号进栈
	// 一直到最终输出后缀表达式为止
	while(a!='\n'&&!ObjTR.IsEmpty())	//转换过程
	{
		if(!IsOperator(a))	//	数字
		{
			printf("%d ",atoi(&a));
			PostFixFormal.Push(a);
		}
		else			// 操作符
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

	while (!PostFixFormal.IsEmpty())  // 将顺序逆转了一下
	{ 
		PostFix.Push(PostFixFormal.Pop());
	}

	PostFixFormal.FreeStack();		// 现在 PostFix 弹出的顺序就是 正常的顺序

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
			ObjND.Push(Calculate(ObjND.Pop(),ObjND.Pop(),x)); // 在这里必须注意运算顺序
		}													// 是最右边的Pop最先开始
	}


	printf("\n所得结果为%d \n",ObjND.Pop());

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
char Precede(char a ,char b)//2012-6-27 从新写    高->低 ) * / + -  (  \n   2012-9-2 从新写
{
	switch (b)				// 应该是( 的运算级最低 因为我们遇到（的时候我们就要将其紧挨着的 + - * / 操作符都入栈 要入栈 条件就是 
	{						// 非括号的运算符 则栈顶运算符与当前运算符做比较 若低于  则入栈 
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