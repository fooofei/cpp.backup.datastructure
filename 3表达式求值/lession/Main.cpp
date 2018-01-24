#include "LineStack.h"

bool IsTrue(char a);
int Calc(int i ,int j,char f);
char Precede(char a ,char b);

void main ()
{
	LineStack<char> ObjTR;
	LineStack<int> ObjND;
	int i =0;
	int j =0;
	char f = 0;
	
	ObjTR.InitStack();
	ObjND.InitStack();
	

	cout<<"请输入表达式"<<endl;
	ObjTR.Push('\n');
	char x = 0;
	char a = getchar();
	while (a!='\n'||x!='\n')
	{
		if (a>='0'&&a<='9')
		{
			ObjND.Push(a-48);
			a = getchar();
		}
		

		else
		{
			if(IsTrue(a))
			{
				switch (Precede(x,a))
				{
				case '<':
					{
						ObjTR.Push(a);
						a = getchar();
						break;
					}
				case '>':
					{
						ObjND.Pop(i);
						ObjND.Pop(j);
						ObjTR.Pop(f);
						ObjND.Push(Calc(i,j,f));
						break;
					}
				case '=':
					{
						ObjTR.Pop(x);
						a = getchar();
						break;
					}
				default:
					{
						a = getchar();
						break;
					}
				}//switch
			}//if
			else
			{
				cout<<"有非法字符"<<endl;
				exit(1);
			}
			
		}//else
		 ObjTR.GetTop(x);
	}


	int m = 0;
	ObjND.Pop(m);
	cout<<"="<<m<<endl;
	
	ObjTR.FreeStack();
	ObjND.FreeStack();
	
}



bool IsTrue(char a)
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

int Calc(int i ,int j,char f)
{
	switch (f)
	{
	case '+':
		{
			return i+j;
		}
	case '-':
		{
			return j-i;
		}
	case '*':
		{
			return j*i;
		}
	case '/':
		{
			return j/i;
		}
	}
}

char Precede(char a ,char b)
{
	switch (b)
	{
	case '+':
	case '-':if (a=='('||a=='\n')
			 {
				 return '<';
			 }
			 else
			 {
				 return '>';
			 }
			
			
	case '*':
	case '/':
		if(a=='*'||a=='/'||a==')')
		{
			return '>';	
		}
		else
		{
			return '<';
		}
		
	case '(':
		{
			if(a==')')
			{
				cout<<"括号不匹配"<<endl;
				exit(1);
			}
			else
			{
				return '<';
			}
			
		}
	case ')':
		{
			switch(a)
			{
			case '(':
				return '=';
			case '\n':
				cout<<"缺乏左括号"<<endl;
				exit(1);
			default:
				return '>';
			}
		
		}
	case '\n':
		{
			switch(a)
			{
			case '\n':
				return '=';
			case '(':
				cout<<"缺乏右括号"<<endl;
				exit(1);
			default :
				return '>';
			}
			
		}
	}

}