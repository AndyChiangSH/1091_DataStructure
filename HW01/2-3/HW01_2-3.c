//4108056005_2-3.cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK 2000

typedef struct		//結構: 四個方向
{
	short int vert;
	short int horiz;
}offsets;

offsets move[6];

typedef struct		//結構: stack 走經的路徑 
{
	char alp;		//字母 
	short int flo;	//樓層 
	short int row;	//橫列 
	short int col;	//直行 
	short int dir;	//方向 
}element;

element stk[MAX_STACK];
int top=-1;

FILE *fin;
FILE *fout;

element pop()
{
	if(top<=-1)
	{
		printf("stack is empty!\n");
	}
	else
	{
		return stk[top--];
	}
}

void push(element item)
{
	if(top>=MAX_STACK-1)
	{
		printf("stack is full!\n");
	}
	else
	{
		stk[++top]=item;
	}
}

void setMove()
{	
	//往上
	move[0].vert=-1; 
	move[0].horiz=0;
	
	//往右
	move[1].vert=0; 
	move[1].horiz=1;
	
	//往下 
	move[2].vert=1;
	move[2].horiz=0;
	
	//往左 
	move[3].vert=0;
	move[3].horiz=-1;
	
	//上樓 
	move[4].vert=0;
	move[4].horiz=0;
	
	//下樓 
	move[5].vert=0;
	move[5].horiz=0;
}

int find_path(int num)
{	
	//前面都在處理讀檔 
	char fin_name[12]="";
	
	sprintf(fin_name,"test%d.txt",num);

	printf("%s finding the path...\n",fin_name);
	
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}	
	
	int n=0;	//計算第一層樓的大小n 
	char ch;
	while((ch=fgetc(fin))!='\n')
	{
		if(ch==' ')
		{
			n++;
		}				
	}
	int total_floor=n/2+1;		//轉換成樓層數 
	rewind(fin);
	
	int i,j,k;
	char maze[total_floor][n+2][n+2];
	int mark[total_floor][n+2][n+2];
	
	//mark歸零
	for(k=0;k<total_floor;k++)
	{
		for(i=0;i<n+2;i++)
		{
			for(j=0;j<n+2;j++)
			{
				mark[k][i][j]=0;
			}
		}
	} 
	
	for(i=0;i<total_floor;i++)	//圍牆一圈比一圈小 
	{
		for(j=i;j<n+2-i;j++)
		{
			maze[i][i][j]='X';
			maze[i][n+1-i][j]='X';
			maze[i][j][i]='X';
			maze[i][j][n+1-i]='X';
		}
	}
	
	int sFlo,sRow,sCol,pNum=0;		//讀檔時，地圖要放在正中央 
	
	for(k=0;k<total_floor;k++)
	{
		for(i=k+1;i<=n-k;i++)
		{
			for(j=k+1;j<=n-k;j++)
			{
				fscanf(fin,"%c ",&maze[k][i][j]);
				if(k==0 && maze[k][i][j]=='S')
				{
					sFlo=k;
					sRow=i;
					sCol=j;
				}
				if(maze[k][i][j]=='P')
				{
					pNum++;
				}
			}
		}
	}	
	
	//找路徑開始 
	int flo,row,col,nextFlo,nextRow,nextCol,dir,posi=0,cost=0,count=0,pContinue=0,min=99;
	int found=0,countable=1;
	element cordi;
	mark[sFlo][sRow][sCol]=1;
	top=0;
	stk[0].flo=sFlo;
	stk[0].row=sRow;
	stk[0].col=sCol;
	stk[0].dir=0;
	
	//用深度算出可能數 
	while(top>-1)	//當所有O都走過 
	{
		cordi=pop();	//取出stack頂端的資料
		//如果取出的這點和它的上一點都是P的話，代表兩個P相連，所以要pContinue要-- 
		if(cordi.alp=='P' && maze[flo][row][col]=='P')
		{
			pContinue--;
		}		
		flo=cordi.flo;
		row=cordi.row;
		col=cordi.col;
		dir=cordi.dir;		
		if(cordi.alp=='T')		//取出T時，cost要減3回去才對 
		{
			cost-=3;
		}
		else
		{
			cost--;
		}
		
		
		while(dir<6)	//當所有方向都走過
		{
			if(dir==4 && (maze[flo][row][col]=='U' || maze[flo][row][col]=='P') && flo!=total_floor-1)	//可上樓的情況 
			{
				nextFlo=flo+1;
			}
			else if(dir==5 && (maze[flo][row][col]=='D' || maze[flo][row][col]=='P') && flo!=0)		//可下樓的情況 
			{
				nextFlo=flo-1;
			}
			else
			{
				nextFlo=flo;
			}						
			nextRow=row+move[dir].vert;
			nextCol=col+move[dir].horiz;
			
			if(maze[nextFlo][nextRow][nextCol]=='F')		//找到終點 
			{
				found=1;
				dir++;
				if(pContinue==pNum-1)	//符合走完整條P路徑的條件 
				{
					count++;
					if(cost+2<min)		//才來求最小值 
					{
						min=cost+2;
					}
				}
			}
			else if(maze[nextFlo][nextRow][nextCol]!='X' && mark[nextFlo][nextRow][nextCol]==0)	//移動 
			{
				mark[nextFlo][nextRow][nextCol]=1;		
				if(maze[flo][row][col]=='T')	//踩在T上時，cost加上3 
				{
					cost+=3;
				}
				else
				{
					cost++;
				}
				if(maze[flo][row][col]=='P')
				{
					if(maze[nextFlo][nextRow][nextCol]=='P')
					{
						pContinue++;
					} 
				} 
				cordi.alp=maze[flo][row][col];
				cordi.flo=flo;
				cordi.row=row;
				cordi.col=col;
				cordi.dir=++dir;
				push(cordi);				
				flo=nextFlo;
				row=nextRow;
				col=nextCol;
				dir=0;
			}
			else
			{
				++dir;
			}
		}
		mark[flo][row][col]=0;	//回推的時候要把走過的路復原回0，不然其他路線會沒辦法走
	}	
	
	//印出結果 
	if(found && count!=0)	//找到一條以上通過P的路徑 
	{
		printf("test %d starts now.\n",num);
		printf("Shortest path: %d, The number of different paths: %d\n\n",min,count);
		fprintf(fout,"test %d starts now.\n",num);
		fprintf(fout,"Shortest path: %d, The number of different paths: %d\n\n",min,count);
	}
	else
	{
		printf("test %d starts now.\n",num);
		printf("This maze doesn't have a path\n\n");
		fprintf(fout,"test %d starts now.\n",num);
		fprintf(fout,"This maze doesn't have a path\n\n");
	}
	
	fclose(fin);	
	return 0;
}

int main()
{
	//開output檔案 
	fout=fopen("output.txt","w");
	if(fout==NULL)
	{
		printf("\nError: Can't find the output file!\n");
		return 0;
	}
	setMove();
	
	int num;
	
	for(num=1;num<=100;num++)
	{
		find_path(num);
	}	
//	find_path(1);
	
	fclose(fout);
	printf("-----File is done!-----\n\n");
	
	return 0;
}
