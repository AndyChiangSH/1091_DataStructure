//4108056005_1-1.cpp

#include <stdio.h>
#define MAX_STACK 1000

typedef struct		//結構: 四個方向
{
	short int vert;
	short int horiz;
} offsets;

offsets move[4];

FILE *fin;

void setMove()
{
	move[0].vert=-1;	//往上
	move[0].horiz=0;

	move[1].vert=0;		//往右
	move[1].horiz=1;

	move[2].vert=1;		//往下
	move[2].horiz=0;

	move[3].vert=0;		//往左
	move[3].horiz=-1;
}

int find_path()
{
	//////////////////////////////////////////////////////////////改檔名在此 
	
	char fin_name[]="test.txt";
	
	/////////////////////////////////////////////////////////////////////// 
	printf("%s now reading...\n",fin_name);
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}	
	
	int n;
	fscanf(fin,"%d",&n);

	int i,j;
	char maze[n+2][n+2];
	int mark[n+2][n+2];
	int bmark[n+2][n+2];

	//mark歸零	
	for(i=0; i<n+2; i++)
	{
		for(j=0; j<n+2; j++)
		{
			mark[i][j]=0;
			bmark[i][j]=99;
		}
	}

	for(i=0; i<n+2; i++)		//初始化陣列(蓋起圍牆)
	{
		maze[0][i]='X';
		maze[n+1][i]='X';
		maze[i][0]='X';
		maze[i][n+1]='X';
	}

	int sRow,sCol;
	fscanf(fin,"%d");	//讀取'/0'
	for(i=1; i<n+1; i++)
	{
		for(j=1; j<n+1; j++)
		{
			fscanf(fin,"%c ",&maze[i][j]);
			if(maze[i][j]=='S')		//紀錄開始的時間
			{
				sRow=i;
				sCol=j;
			}
		}
	}
	//找路徑開始
	int row,col,nextRow,nextCol,dir;
	int bfound=0,endB;
	mark[sRow][sCol]=1;
	bmark[sRow][sCol]=0;
	int end_row,end_col;

	//用廣度跑
	int l,b=0;
	while(!bfound)		//每次b++，找到一條路徑後結束
	{
		endB=1;
		for(i=1; i<n+1; i++)
		{
			for(j=1; j<n+1; j++)
			{
				if(bmark[i][j]>=b+2)
					endB=0;
				if(bmark[i][j]==b)		//如果等於最大的數字+1
				{
					endB=0;
					for(l=0; l<4; l++)
					{
						nextRow=i+move[l].vert;
						nextCol=j+move[l].horiz;
						if(maze[nextRow][nextCol]=='F')	//找到重點
						{
							bfound=1;
							bmark[nextRow][nextCol]=b+1;
							end_row=nextRow;
							end_col=nextCol;
						}
						else if(maze[nextRow][nextCol]!='X')	//可以移動
						{
							if(b+1<bmark[nextRow][nextCol])
							{
								bmark[nextRow][nextCol]=b+1;	//路徑+1
							}
						}
					}
				}
			}
		}
		if(endB)	//沒有路徑要跳出
		{
			break;
		}
		b++;
	}

	if(bfound)		//有找到路徑
	{
		int row=end_row,col=end_col,dir;
		int preRow,preCol;

		for(i=b; i>=0; i--)	//從終點連一條路徑回去
		{
			dir=0;
			while(dir<4)
			{
				preRow=row+move[dir].vert;
				preCol=col+move[dir].horiz;
				if(bmark[preRow][preCol]==i-1)	//找到自己數字-1的位置
				{
					mark[row][col]=1;
					row=preRow;
					col=preCol;
					break;
				}
				dir++;
			}
		}

		//印出結果
		for(i=1; i<n+1; i++)
		{
			for(j=1; j<n+1; j++)
			{
				if(mark[i][j]==1)
				{
					printf("* ");
				}
				else
				{
					printf("%-2c",maze[i][j]);
				}
			}
			printf("\n");
		}
		printf("Path length: %d\n",b);
	}
	else
	{
		printf("This maze doesn't have a path\n");
	}

	fclose(fin);
	return 0;
}

int main()
{
	setMove();
	find_path();
	
	return 0;
}
