#ifndef HEAD  
#define HEAD  

class TNode//�����  
{    
public:  
	char oper;  
	TNode *left;  
	TNode *right;  
	//��ӡʱʹ�ã���Ǹ�Ԫ���ڵ�s��ĵ�t��λ��  
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