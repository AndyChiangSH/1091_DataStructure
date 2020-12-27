//4108056005_1-1.cpp

#include <stdio.h>
#define MAX_STACK 1000

typedef struct		//���c: �|�Ӥ�V
{
	short int vert;
	short int horiz;
} offsets;

offsets move[4];

FILE *fin;

void setMove()
{
	move[0].vert=-1;	//���W
	move[0].horiz=0;

	move[1].vert=0;		//���k
	move[1].horiz=1;

	move[2].vert=1;		//���U
	move[2].horiz=0;

	move[3].vert=0;		//����
	move[3].horiz=-1;
}

int find_path()
{
	//////////////////////////////////////////////////////////////���ɦW�b�� 
	
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

	//mark�k�s	
	for(i=0; i<n+2; i++)
	{
		for(j=0; j<n+2; j++)
		{
			mark[i][j]=0;
			bmark[i][j]=99;
		}
	}

	for(i=0; i<n+2; i++)		//��l�ư}�C(�\�_����)
	{
		maze[0][i]='X';
		maze[n+1][i]='X';
		maze[i][0]='X';
		maze[i][n+1]='X';
	}

	int sRow,sCol;
	fscanf(fin,"%d");	//Ū��'/0'
	for(i=1; i<n+1; i++)
	{
		for(j=1; j<n+1; j++)
		{
			fscanf(fin,"%c ",&maze[i][j]);
			if(maze[i][j]=='S')		//�����}�l���ɶ�
			{
				sRow=i;
				sCol=j;
			}
		}
	}
	//����|�}�l
	int row,col,nextRow,nextCol,dir;
	int bfound=0,endB;
	mark[sRow][sCol]=1;
	bmark[sRow][sCol]=0;
	int end_row,end_col;

	//�μs�׶]
	int l,b=0;
	while(!bfound)		//�C��b++�A���@�����|�ᵲ��
	{
		endB=1;
		for(i=1; i<n+1; i++)
		{
			for(j=1; j<n+1; j++)
			{
				if(bmark[i][j]>=b+2)
					endB=0;
				if(bmark[i][j]==b)		//�p�G����̤j���Ʀr+1
				{
					endB=0;
					for(l=0; l<4; l++)
					{
						nextRow=i+move[l].vert;
						nextCol=j+move[l].horiz;
						if(maze[nextRow][nextCol]=='F')	//��쭫�I
						{
							bfound=1;
							bmark[nextRow][nextCol]=b+1;
							end_row=nextRow;
							end_col=nextCol;
						}
						else if(maze[nextRow][nextCol]!='X')	//�i�H����
						{
							if(b+1<bmark[nextRow][nextCol])
							{
								bmark[nextRow][nextCol]=b+1;	//���|+1
							}
						}
					}
				}
			}
		}
		if(endB)	//�S�����|�n���X
		{
			break;
		}
		b++;
	}

	if(bfound)		//�������|
	{
		int row=end_row,col=end_col,dir;
		int preRow,preCol;

		for(i=b; i>=0; i--)	//�q���I�s�@�����|�^�h
		{
			dir=0;
			while(dir<4)
			{
				preRow=row+move[dir].vert;
				preCol=col+move[dir].horiz;
				if(bmark[preRow][preCol]==i-1)	//���ۤv�Ʀr-1����m
				{
					mark[row][col]=1;
					row=preRow;
					col=preCol;
					break;
				}
				dir++;
			}
		}

		//�L�X���G
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
