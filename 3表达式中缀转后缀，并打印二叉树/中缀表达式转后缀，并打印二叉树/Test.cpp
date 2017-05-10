#include <iostream>  
#include <string>  
using namespace std;  

#include "func.h"  

int main()  
{  
	string expression;  
	TNode *tree;  
	cout<<endl<<"请输入中缀表达式: ";  
	cin>>expression;  

	//将中缀表达式转换为后缀表达式  
	Postfix_exp(tree,expression);  
	//打印二叉树  
	Print_tree(tree);  
	//释放树  
	Free_tree(tree);  

	cout<<endl<<endl;  
	system("pause");  
	return 0;  
}  