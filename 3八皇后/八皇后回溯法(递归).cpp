#include <stdio.h>
#include <stdlib.h>
#define N 4

int column[N+1]; // ͬ���Ƿ��лʺ�1��ʾû��
int rup[2*N+1]; // �����������Ƿ��лʺ�  N ���ʺ�� ���� �� ���� ��2 ���Ĺ�ϵ
int lup[2*N+1]; // �����������Ƿ��лʺ�
int queen[N+1] = {0};

// ����һ��  ��������   
// ���Ǵ� �Ļʺ� һ���� ����������  �������ʺ� �� ���� �����µ� ��ϵ��ʱ�� ��ô���ǵ�λ������ 
//  ��+ ��  =  ��+ ��

// ���� ���� ������ ��ʱ��  ��ô���� �� -��  =  �� - �� 


// ����ԭ��ʹ�õķ���Ҳ�ǵݹ����   
// ����ֻ���ڵݹ�� ��֤�Ƿ���԰���ʺ���㷨�в�ͬ   
// ������ ʹ���˸���Ĵ洢�ռ�����¼�Ƿ���Է� �ʺ�  
void backtrack(int); // �ݻ����

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
		static int num = 0;// �����
    printf("��� %d\n", ++num);
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


// i ����  �� �� 
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
                // �趨Ϊռ��
                column[j] = rup[i+j] = lup[i-j+N] = 0;
                backtrack(i+1);
                column[j] = rup[i+j] = lup[i-j+N] = 1;
            }
        }
    }
}
