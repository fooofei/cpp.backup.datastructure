#ifndef HEAD  
#define HEAD  

class TNode//结点类  
{    
public:  
	char oper;  
	TNode *left;  
	TNode *right;  
	//打印时使用，标记该元素在第s层的第t个位置  
	int s;  
	int t;  
	TNode()  
	{  
		left=right=NULL;  
		oper=0;  
	}  
	TNode(char op)  
	{  
		left=right=NULL;  
		oper=op;  
	}  
};  

#endif  