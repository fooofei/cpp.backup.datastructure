#include <iostream>  
#include <string>  
using namespace std;  

#include "func.h"  

int main()  
{  
	string expression;  
	TNode *tree;  
	cout<<endl<<"��������׺���ʽ: ";  
	cin>>expression;  

	//����׺���ʽת��Ϊ��׺���ʽ  
	Postfix_exp(tree,expression);  
	//��ӡ������  
	Print_tree(tree);  
	//�ͷ���  
	Free_tree(tree);  

	cout<<endl<<endl;  
	system("pause");  
	return 0;  
}  