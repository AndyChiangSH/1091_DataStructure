//4108056005_2-1.cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct		//結構: 四個方向
{
	short int vert;
	short int horiz;
}offsets;

offsets move[6];

FILE *fin;
FILE *fout;

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
		
	fout=fopen(fout_name,"w");
	if(fout==NULL)
	{
		printf("\nError: Can't find the output file!\n");
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
	int flo,row,col,nextFlo,nextRow,nextCol,dir,posi=0,min=100,cost=0;
	int bfound=0,endB;
	mark[sFlo][sRow][sCol]=1;
	bmark[sFlo][sRow][sCol]=0;
	int end_floor,end_row,end_col;
	
	//第一次用廣度跑
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
			break;
		}
		b++;
	}
	 
	if(bfound)		//有找到路徑 
	{
		int flo=end_floor,row=end_row,col=end_col,dir;
		int preFlo,preRow,preCol;
		
		for(i=b;i>=0;i--)	//從終點連一條路徑回去 
		{
			dir=0;
			while(dir<6)
			{
				if(dir==4)
				{
					preFlo=flo+1;
				}
				else if(dir==5)
				{
					preFlo=flo-1;	
				}
				else
				{
					preFlo=flo;
				}
				preRow=row+move[dir].vert;
				preCol=col+move[dir].horiz;
				if(bmark[preFlo][preRow][preCol]==i-1)	//找到自己數字-1的位置 
				{
					mark[flo][row][col]=1;
					flo=preFlo;
					row=preRow;
					col=preCol;
					break;
				}
				dir++;
			}
		}
		
		printf("Path length: %d\n",b);		//印出結果 
//		printf("=====outMaze=====\n");			
//		for(k=0;k<total_floor;k++)
//		{
//			for(i=k+1;i<n+1-k;i++)
//			{
//				for(j=k+1;j<n+1-k;j++)
//				{
//					if(mark[k][i][j]==1)
//					{
//						printf("* ");
//					}
//					else
//					{
//						printf("%-2c",maze[k][i][j]);
//					}
//				}
//				printf("\n");
//			}
//			printf("\n");
//		}
		
		fprintf(fout,"Path length: %d\n",b);	//寫檔 
		fprintf(fout,"=====outMaze=====\n");			
		for(k=0;k<total_floor;k++)
		{
			for(i=k+1;i<n+1-k;i++)
			{
				for(j=k+1;j<n+1-k;j++)
				{
					if(mark[k][i][j]==1)
					{
						fprintf(fout,"* ");
					}
					else
					{
						fprintf(fout,"%-2c",maze[k][i][j]);
					}
				}
				fprintf(fout,"\n");
			}
			fprintf(fout,"\n");
		}
	}
	else
	{
		printf("This maze doesn't have a path\n");
		fprintf(fout,"This maze doesn't have a path\n");
	}

	fclose(fin);
	fclose(fout);
	printf("-----File is done!-----\n\n");
}

int main()
{
	setMove();
	
	int num;
	
	for(num=1;num<=100;num++)
	{
		find_path(num);
	}
//	find_path(1);

	return 0;
}
