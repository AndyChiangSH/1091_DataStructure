//4108056005_hw2_1-3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fin;

int readFile(int num)
{
	//讀檔部分 
	char fin_name[12]="";
	sprintf(fin_name,"test%d.txt",num);
	printf("%s now reading...\n",fin_name);
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}

	int N,M,i,j,k,input=0;
	fscanf(fin,"%d",&N);	//讀入N 
	fscanf(fin,"%d",&M);	//讀入M 

	int count[N][N];	//計算一句話中每個俘虜出現的次數 
	char compare[N],ch;	//敘述最後面後的那個T/L，之後會拿來跟enu比較 
	char enu[N];		//這邊先建立列舉用的陣列，之後會跟compare比較 
	for(i=0; i<N; i++)	//初始陣列 
	{
		for(j=0; j<N; j++)
		{
			count[i][j]=0;
		}
	}
	for(i=0; i<N; i++)
	{
		fscanf(fin,"%d>",&j);
		while((ch=fgetc(fin))!='=')	//讀到'='敘述結束 
		{
			if(ch!='>')	//讀到'>'分隔數字
			{
				input=(input*10)+(int)(ch-48);
			}
			else
			{
				count[i][input]++;	//累積騙子的個數 
				input=0;
			}
		}
		count[i][input]++;
		input=0;
		fscanf(fin,"%c",&compare[i]);	//讀去最後的T/L 
	}
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			count[i][j]=count[i][j]%2;	//兩兩一對可以消除(TT和LL不影響結果) 
		}
	}
	//讀檔部分結束 
	
	int pos[M];	//存放列舉中，哪幾個人是騙子 
	short int found=0;
	for(i=0; i<M; i++)	//初始化 
	{
		pos[i]=i;
	}
	pos[M-1]--;
	while(1)	//找到就會跳出
	{
		//這部分是用來處理列舉條件的替換 
		short int change=0;
		for(j=0; j<M; j++)
		{
			if(pos[j]==N-M+j)	//N-M+j代表數字到底的值 
			{
				if(j==0)	//當第一個騙子到底時，代表所有可能都跑過了，結束迴圈 
				{
					break;
				}
				pos[j-1]++;	//把上一個加一 
				for(k=j; k<M; k++)
				{
					pos[k]=pos[j-1]+(k-j+1);	//並把之後的數字都貼在第一個數字之後 
				}
				change=1;
				break;
			}
		}
		if(j==0)
		{
			break;
		}
		if(change==0)	//沒有數字碰到底的情況，最後一個數字加一 
		{
			pos[M-1]++;
		}
		//列舉替換結束 
		
		for(i=0; i<N; i++)
		{
			enu[i]='T';
		}
		for(i=0; i<M; i++)
		{
			enu[pos[i]]='L';	//把騙子設為L 
		}

		short int wrong=0;
		for(i=0; i<N; i++)
		{
			int lnum=0;
			for(j=0; j<M; j++)
			{
				lnum=lnum+count[i][pos[j]];	//累積騙子的數量 
			}
			if(lnum%2==0)	//有偶數個L，結果相同
			{
				if(compare[i]!=enu[i])	//結果相反，有問題
				{
					wrong=1;
				}
			}
			else	//有奇數個L，結果相反
			{
				if(compare[i]==enu[i])	//結果相同，有問題
				{
					wrong=1;
				}
			}
			if(wrong) //有錯誤，直接跳回while迴圈開頭 
			{
				break;
			}
		}
		if(!wrong)	//全部敘述都正確 
		{
			found=1;
			break;			
		}
	}

	if(found)	//輸出部分 
	{
		printf("test%d:",num);
		for(i=0; i<M; i++)
		{
			printf(" %d",pos[i]);
		}
		printf("\n");
	}
	else
	{
		printf("Wrong input!\n");
	}

	fclose(fin);
	return 0;
}

int main()
{	
	//讀檔在這裡!!!///////////////////////////////////////////////////////////////////////////
	
	readFile(1);	//輸入數字0代表讀test0.txt，依此類推
	
	////////////////////////////////////////////////////////////////////////////////////////// 

	return 0;
}
