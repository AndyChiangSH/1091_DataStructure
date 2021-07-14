//4108056005_hw04_Q3
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fin;

void lookMap(char*,int*,int);	//印出豪宅地圖 
int lookInfo(char*,int*,int);	//實際跑過每個窗戶，檢查有沒有跟題目給的一樣 
int dfs(char*,char*,int*,int,int,int,int,int);	//深度搜尋(優化過) 

int main() 
{
	//////////////////////////////////////////////////////////////改檔名在此 
	
	char fin_name[]="test3.txt";
	
	/////////////////////////////////////////////////////////////////////// 
	printf("%s now reading...\n",fin_name);
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}	
	
	int i,j;
	int N,Vcount,Zcount,Gcount;
	fscanf(fin,"%d %d %d",&Vcount,&Zcount,&Gcount);
	printf("Vcount : %d\n",Vcount);
	printf("Zcount : %d\n",Zcount);
	printf("Gcount : %d\n",Gcount);
	fscanf(fin,"%d",&N);
	int visible[4][N];	//四邊窗戶看到的怪物數量 
	for(i=0;i<4;i++)
	{
		for(j=0;j<N;j++)
		{
			fscanf(fin,"%d",&visible[i][j]);
		}
	}
	char map[N][N];	//豪宅地圖 
	char origin[N][N];	//維持地圖原狀，程式執行時不會影響他 
	fgetc(fin);
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			map[i][j]=fgetc(fin);
			origin[i][j]=map[i][j];
		}
		fgetc(fin);
	}
	
	//做深度搜尋 
	dfs(&origin[0][0],&map[0][0],&visible[0][0],0,N,Vcount,Zcount,Gcount);

	fclose(fin);
	return 0;
}

void lookMap(char* ptr,int* vis,int n)
{
	//ptr = &map[0][0] 
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%c",*(ptr+(i*n)+j));
		}
		printf("\n");
	}
}

int lookInfo(char* ptr,int* vis,int n)
{
	//ptr = &map[0][0]
	/*回傳0  -> 有一條視線有錯
	  回傳1 -> 無論是否已經填滿，所有已經連成一條的視線都是對的*/ 
	int i,j,x,y,dir;
	for(j=0;j<4;j++)
	{
		for(i=0;i<n;i++)
		{
			short int mirror=0;
			int count=0;
			if(j==0)	//從上面窗戶 
			{
				x=-1;
				y=i;
				dir=2;
			}
			else if(j==1)	//從下面窗戶 
			{
				x=n;
				y=i;
				dir=0;				
			}
			else if(j==2)	//從左邊窗戶 
			{
				x=i;
				y=-1;
				dir=1;				
			}
			else if(j==3)	//從右邊窗戶 
			{
				x=i;
				y=n;
				dir=3;				
			}
			while(1)
			{
				if(dir==0) 	//方向向上 
				{
					x--;
					if(*(ptr+(x*n)+y)=='\\')
					{
						dir=3;	//轉左 
						mirror=1;
					}
					else if(*(ptr+(x*n)+y)=='/')
					{
						dir=1;	//轉右 
						mirror=1;
					}
				}
				else if(dir==1)	//方向向右 
				{
					y++;
					if(*(ptr+(x*n)+y)=='\\')
					{
						dir=2;	//轉下 
						mirror=1;
					}
					if(*(ptr+(x*n)+y)=='/')
					{
						dir=0;	//轉上 
						mirror=1;
					}
				}
				else if(dir==2)	//方向向下 
				{
					x++;
					if(*(ptr+(x*n)+y)=='\\')
					{
						dir=1;	//轉右
						mirror=1; 
					}
					if(*(ptr+(x*n)+y)=='/')
					{
						dir=3;	//轉左 
						mirror=1;
					}
				}
				else if(dir==3)	//方向向左 
				{
					y--;
					if(*(ptr+(x*n)+y)=='\\')
					{
						dir=0; 	//轉上 
						mirror=1;
					}
					if(*(ptr+(x*n)+y)=='/')
					{
						dir=2;	//轉下 
						mirror=1;
					}
				}
				
				if(*(ptr+(x*n)+y)=='.')	//視線未完整，跳出 
				{
					break;
				}				
				if(x<0 || x>n-1 || y<0 || y>n-1)	//超出範圍就跳出迴圈 
				{
					if(*(vis+(j*n)+i)!=count)
					{
						return 0;
					}
					break;
				}
				
				if(mirror==0)	//未通過鏡子，看的到殭屍、吸血鬼 
				{
					if(*(ptr+(x*n)+y)=='Z' || *(ptr+(x*n)+y)=='V')
					{
						count++;
					}
				}
				else	//通過鏡子，看的到殭屍、鬼魂 
				{
					if(*(ptr+(x*n)+y)=='Z' || *(ptr+(x*n)+y)=='G')
					{
						count++;
					}
				}
			}
		}	
	}
	return 1;
}

int time=0;	//紀錄遞迴次數 
int dfs(char* ori,char* map,int* vis,int x,int n,int Vcount,int Zcount,int Gcount)
{
//	lookMap(map,vis,n);
	/*回傳0 -> 代表這條路以下都是錯的
	  回傳1 -> 代表已經有解答了*/
	while(*(ori+x)!='.')	//找出下一塊空格
	{
		x++;
	}
	if(!lookInfo(map,vis,n))	//如果有錯，那也不要再往下遞迴了，並且往回退 
	{
		time++;
		return 0;
	}
	if(Vcount==0 && Zcount==0 && Gcount==0)	//填滿空格 
	{
		printf("time = %d\n",time);
		lookMap(map,vis,n);	//正確解答 
		return 1;	//找到解答後回傳1，不用再繼續找下去了 
	}
	else
	{
		if(Vcount>0)	//如果吸血鬼還有剩 
		{
			*(map+x)='V';
			if(dfs(ori,map,vis,x+1,n,Vcount-1,Zcount,Gcount))
			{
				return 1;
			}
			else
			{
				*(map+x)='.';	//回復成未走過
			}				
		}
		if(Zcount>0)	//如果殭屍還有剩  
		{
			*(map+x)='Z';
			if(dfs(ori,map,vis,x+1,n,Vcount,Zcount-1,Gcount))
			{
				return 1;
			}
			else
			{
				*(map+x)='.';	//回復成未走過 
			}	
		}
		if(Gcount>0)	//如果鬼魂還有剩 
		{
			*(map+x)='G';
			if(dfs(ori,map,vis,x+1,n,Vcount,Zcount,Gcount-1))
			{
				return 1;
			}
			else
			{
				*(map+x)='.';	//回復成未走過
			}	
		}
	}
	return 0;
}
