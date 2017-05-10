#include <stdio.h>
#include <stdlib.h>
#define N 4

int column[N+1]; // 同列是否有皇后，1表示没有
int rup[2*N+1]; // 右上至左下是否有皇后  N 个皇后的 右上 和 左下 共2 倍的关系
int lup[2*N+1]; // 左上至右下是否有皇后
int queen[N+1] = {0};

// 调试一下  就明白了   
// 我们从 四皇后 一个简单 的例子来看  当两个皇后 是 右上 至左下的 关系的时候 那么他们的位置满足 
//  行+ 列  =  行+ 列

// 当是 左上 至右下 的时候  那么就是 行 -列  =  行 - 列 


// 我们原来使用的方法也是递归求解   
// 区别只是在递归的 求证是否可以安插皇后的算法中不同   
// 本代码 使用了更多的存储空间来记录是否可以放 皇后  
void backtrack(int); // 递回求解

 int main() {
    int i;
    for(i = 1; i <= N; i++)
        column[i] = 1;
	
    for(i = 1; i <= 2*N; i++)
        rup[i] = lup[i] = 1;
	
    backtrack(1);
	
    return 0;
}

void showAnswer() 
{
    int x, y;
		static int num = 0;// 解答编号
    printf("解答 %d\n", ++num);
    for(y = 1; y <= N; y++) 
		{
        for(x = 1; x <= N; x++) 
				{
            if(queen[y] == x) {
                printf(" Q");
            }
            else {
                printf(" .");
            }
        }
        printf("\n");
    }
}


// i 是行  定 行 
void backtrack(int i) {
    int j;
	
    if(i > N) {
        showAnswer();
    }
    else 
		{
        for(j = 1; j <= N; j++) 
				{
            if(column[j] == 1 &&
				rup[i+j] == 1 && lup[i-j+N] == 1) 
						{
                queen[i] = j;
                // 设定为占用
                column[j] = rup[i+j] = lup[i-j+N] = 0;
                backtrack(i+1);
                column[j] = rup[i+j] = lup[i-j+N] = 1;
            }
        }
    }
}
