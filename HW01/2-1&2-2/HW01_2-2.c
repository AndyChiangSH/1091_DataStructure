//4108056005_2-2.cpp

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
	char fout_name[16]="";
	
	sprintf(fin_name,"test%d.txt",num);
	sprintf(fout_name,"test%d_ans.txt",num);

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
	int bmark[total_floor][n+2][n+2];
	
	//mark歸零
	for(k=0;k<total_floor;k++)
	{
		for(i=0;i<n+2;i++)
		{
			for(j=0;j<n+2;j++)
			{
				mark[k][i][j]=0;
				bmark[k][i][j]=99;
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
	
	int sFlo,sRow,sCol;		//讀檔時，地圖要放在正中央 
	
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
			}
		}
	}	
	
	//找路徑開始 
	int flo,row,col,nextFlo,nextRow,nextCol,dir,posi=0,cost=0;
	int found=0,bfound=0,endB;
	element cordi;
	element min_stk[MAX_STACK];		//用來存放最短路徑 
	mark[sFlo][sRow][sCol]=1;
	bmark[sFlo][sRow][sCol]=0;
	top=0;
	stk[0].flo=sFlo;
	stk[0].row=sRow;
	stk[0].col=sCol;
	stk[0].dir=0;
	int end_floor,end_row,end_col;
	
	//第一次先用廣度跑，找出min 
	int l,b=0;
	while(!bfound)		//每次b++，找到一條路徑後結束 
	{
		endB=1;
		for(k=0;k<total_floor;k++)
		{
			for(i=k+1;i<=n-k;i++)
			{
				for(j=k+1;j<=n-k;j++)
				{		
					if(bmark[k][i][j]>=b+2)
						endB=0;			
					if(bmark[k][i][j]==b)		//如果等於最大的數字+1 
					{
						endB=0;
						for(l=0;l<6;l++)
						{
							if(l==4 && maze[k][i][j]=='U' && k!=total_floor-1)	//可上樓的情況 
							{
								nextFlo=k+1;
							}
							else if(l==5 && maze[k][i][j]=='D' && k!=0)		//可下樓的情況 
							{
								nextFlo=k-1;
							}
							else
							{
								nextFlo=k;
							}		
							nextRow=i+move[l].vert;
							nextCol=j+move[l].horiz;
							if(maze[nextFlo][nextRow][nextCol]=='F')	//找到重點 
							{
								bfound=1;
								bmark[nextFlo][nextRow][nextCol]=b+1;
								end_floor=nextFlo;	
								end_row=nextRow;
								end_col=nextCol;							
							}
							else if(maze[nextFlo][nextRow][nextCol]!='X')	//可以移動 
							{
								if(maze[k][i][j]=='T')	//如果是陷阱 
								{
									if(b+3<bmark[nextFlo][nextRow][nextCol])
									{
										bmark[nextFlo][nextRow][nextCol]=b+3;	//路徑+3 
									}
								}
								else
								{
									if(b+1<bmark[nextFlo][nextRow][nextCol])
									{
										bmark[nextFlo][nextRow][nextCol]=b+1;	//路徑+1 
									}
								}
							} 
						}
					}
				}
			}
		}
		if(endB)	//沒有路徑要跳出 
		{
			printf("this is endB\n");
			break;
		}
		b++;
	}
	
	//再用深度算出可能數 
	while(top>-1)	//當所有O都走過 
	{
		cordi=pop();	//取出stack頂端的資料
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
			if(dir==4 && maze[flo][row][col]=='U' && flo!=total_floor-1)	//可上樓的情況 
			{
				nextFlo=flo+1;
			}
			else if(dir==5 && maze[flo][row][col]=='D' && flo!=0)		//可下樓的情況 
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
				if(cost+2<b+5)	//在五步內 
				{
					posi++;
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
				
				if(cost+2>b+5)	//優化: cost大於b+5時，結束這條路徑  (!超重要) 
				{
					break;
				}
			}
			else
			{
				++dir;
			}
		}
		mark[flo][row][col]=0;	//回推的時候要把走過的路復原回0，不然其他路線會沒辦法走
	}	
	
	//印出結果 
	if(found)
	{
		printf("test %d starts now.\n",num);
		printf("Shortest path: %d, Limit: %d, The number of different paths: %d\n\n",b,b+5,posi);
		fprintf(fout,"test %d starts now.\n",num);
		fprintf(fout,"Shortest path: %d, Limit: %d, The number of different paths: %d\n\n",b,b+5,posi);

	}
	else
	{
		printf("test %d starts now.\n",num);
		printf("This maze doesn't have a path\n\n");
		fprintf(fout,"test %d starts now.\n",num);
		fprintf(fout,"This maze doesn't have a path\n\n");
	}
	
	fclose(fin);
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
//	find_path(4);
	
	fclose(fout);
	printf("-----File is done!-----\n\n");
	
	return 0;
}
