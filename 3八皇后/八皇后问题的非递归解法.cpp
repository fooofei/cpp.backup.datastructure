

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
//  �ǵݹ� ʹ���� ȫ���� �������
using namespace std;
const int MAX = 4;

vector<int> board(MAX);

void show_result()
{
//     for(size_t i = 0; i < board.size(); i++)
//         cout<<"("<<i<<","<<board[i]<<")";
//     cout<<endl;


	// �һ�����һ�ִ�ӡ��ʽ   �������ӵ�ֱ��  
		size_t i, j;

		for (i=0;i<board.size() ; ++ i)
		{
			for (j=0;j<board.size() ; ++j)
			{
				if( board[i] == j)
					printf(" Q ");
				else
					printf(" - ");
			}
			printf("\n");
		}
		printf("\n");
}

int check_cross()
{
    for(size_t i = 0; i < board.size()-1; i++)
    {
        for(size_t j = i+1; j < board.size(); j++)
        {
            if((j-i) == (size_t)abs(board[i]-board[j]))
                return 1;
        }
    }
    return 0;
}

//   2013 - 4 - 14 �Լ�д��
int check()
{
	for (size_t i = 0; i < board.size()-1 ; ++ i)
	{
		for(size_t j = i+1; j < board.size() ; ++j)
		{																// �ҿ���б�� 
			if((board[i] == board[j] ) || abs(board[i] - board[j]) == abs(i-j) )
				return 1;
		}
		
	}

	return 0;
}

void put_chess()
{
	// Ŀǰ board �Ǵ��� 0 1 2 3  ������
	// ��Ϊ������ Ŀǰ����  ���� ���ǵõ���������һ��ȫ����
	// ����ÿһ������
    while(next_permutation(board.begin(), board.end()))
    {
        if(!check())
        {
            show_result();
        }
    }
}

int main()
{
    for(size_t i =0; i < board.size(); i++)
        board[i] = i;
    put_chess();
    return 0;
}


	

/*


// next_permutation ����  ������ȫ����

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	string str;
	cin>>str;
  sort(str.begin(), str.end());   // ȫ����   Ԫ����ͬ����ֻ��һ��
	cout<<str<<endl<<"ȫ����Ϊ"<<endl;

	// ������ʹ���� ����֮�� ��û��Ҫʹ�� prev_permutation �� ���û��ʹ������  
	// �Ǿ�Ҫprev_permutation һ���ǲ��� ȫ����
// 	string strCopy(str.c_str());
// 	while (prev_permutation(strCopy.begin() , strCopy.end()))
// 	{
// 			cout<<strCopy<<endl;
// 	}

	while (next_permutation(str.begin(), str.end()))
	{
		cout<<str<<endl;
	}

    return 0;
}*/