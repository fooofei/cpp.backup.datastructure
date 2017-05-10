

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
//  非递归 使用了 全排列 真是天才
using namespace std;
const int MAX = 4;

vector<int> board(MAX);

void show_result()
{
//     for(size_t i = 0; i < board.size(); i++)
//         cout<<"("<<i<<","<<board[i]<<")";
//     cout<<endl;


	// 我换了另一种打印方式   这样更加的直观  
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

//   2013 - 4 - 14 自己写的
int check()
{
	for (size_t i = 0; i < board.size()-1 ; ++ i)
	{
		for(size_t j = i+1; j < board.size() ; ++j)
		{																// 我看作斜率 
			if((board[i] == board[j] ) || abs(board[i] - board[j]) == abs(i-j) )
				return 1;
		}
		
	}

	return 0;
}

void put_chess()
{
	// 目前 board 是存有 0 1 2 3  的数组
	// 因为是数组 目前有序  所以 我们得到的是他的一个全排列
	// 对于每一个排列
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


// next_permutation 讲解  作用是全排列

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	string str;
	cin>>str;
  sort(str.begin(), str.end());   // 全排列   元素相同排列只有一种
	cout<<str<<endl<<"全排列为"<<endl;

	// 当我们使用了 排序之后 就没必要使用 prev_permutation 了 如果没有使用排序  
	// 那就要prev_permutation 一下那才是 全排序
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