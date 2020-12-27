//4108056005_2-3.cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK 2000

typedef struct		//���c: �|�Ӥ�V
{
	short int vert;
	short int horiz;
}offsets;

offsets move[6];

typedef struct		//���c: stack ���g�����| 
{
	char alp;		//�r�� 
	short int flo;	//�Ӽh 
	short int row;	//��C 
	short int col;	//���� 
	short int dir;	//��V 
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
	//���W
	move[0].vert=-1; 
	move[0].horiz=0;
	
	//���k
	move[1].vert=0; 
	move[1].horiz=1;
	
	//���U 
	move[2].vert=1;
	move[2].horiz=0;
	
	//���� 
	move[3].vert=0;
	move[3].horiz=-1;
	
	//�W�� 
	move[4].vert=0;
	move[4].horiz=0;
	
	//�U�� 
	move[5].vert=0;
	move[5].horiz=0;
}

int find_path(int num)
{	
	//�e�����b�B�zŪ�� 
	char fin_name[12]="";
	
	sprintf(fin_name,"test%d.txt",num);

	printf("%s finding the path...\n",fin_name);
	
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}	
	
	int n=0;	//�p��Ĥ@�h�Ӫ��j�pn 
	char ch;
	while((ch=fgetc(fin))!='\n')
	{
		if(ch==' ')
		{
			n++;
		}				
	}
	int total_floor=n/2+1;		//�ഫ���Ӽh�� 
	rewind(fin);
	
	int i,j,k;
	char maze[total_floor][n+2][n+2];
	int mark[total_floor][n+2][n+2];
	
	//mark�k�s
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
	
	for(i=0;i<total_floor;i++)	//����@���@��p 
	{
		for(j=i;j<n+2-i;j++)
		{
			maze[i][i][j]='X';
			maze[i][n+1-i][j]='X';
			maze[i][j][i]='X';
			maze[i][j][n+1-i]='X';
		}
	}
	
	int sFlo,sRow,sCol,pNum=0;		//Ū�ɮɡA�a�ϭn��b������ 
	
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
	
	//����|�}�l 
	int flo,row,col,nextFlo,nextRow,nextCol,dir,posi=0,cost=0,count=0,pContinue=0,min=99;
	int found=0,countable=1;
	element cordi;
	mark[sFlo][sRow][sCol]=1;
	top=0;
	stk[0].flo=sFlo;
	stk[0].row=sRow;
	stk[0].col=sCol;
	stk[0].dir=0;
	
	//�β`�׺�X�i��� 
	while(top>-1)	//��Ҧ�O�����L 
	{
		cordi=pop();	//���Xstack���ݪ����
		//�p�G���X���o�I�M�����W�@�I���OP���ܡA�N����P�۳s�A�ҥH�npContinue�n-- 
		if(cordi.alp=='P' && maze[flo][row][col]=='P')
		{
			pContinue--;
		}		
		flo=cordi.flo;
		row=cordi.row;
		col=cordi.col;
		dir=cordi.dir;		
		if(cordi.alp=='T')		//���XT�ɡAcost�n��3�^�h�~�� 
		{
			cost-=3;
		}
		else
		{
			cost--;
		}
		
		
		while(dir<6)	//��Ҧ���V�����L
		{
			if(dir==4 && (maze[flo][row][col]=='U' || maze[flo][row][col]=='P') && flo!=total_floor-1)	//�i�W�Ӫ����p 
			{
				nextFlo=flo+1;
			}
			else if(dir==5 && (maze[flo][row][col]=='D' || maze[flo][row][col]=='P') && flo!=0)		//�i�U�Ӫ����p 
			{
				nextFlo=flo-1;
			}
			else
			{
				nextFlo=flo;
			}						
			nextRow=row+move[dir].vert;
			nextCol=col+move[dir].horiz;
			
			if(maze[nextFlo][nextRow][nextCol]=='F')		//�����I 
			{
				found=1;
				dir++;
				if(pContinue==pNum-1)	//�ŦX�������P���|������ 
				{
					count++;
					if(cost+2<min)		//�~�ӨD�̤p�� 
					{
						min=cost+2;
					}
				}
			}
			else if(maze[nextFlo][nextRow][nextCol]!='X' && mark[nextFlo][nextRow][nextCol]==0)	//���� 
			{
				mark[nextFlo][nextRow][nextCol]=1;		
				if(maze[flo][row][col]=='T')	//��bT�W�ɡAcost�[�W3 
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
		mark[flo][row][col]=0;	//�^�����ɭԭn�⨫�L�����_��^0�A���M��L���u�|�S��k��
	}	
	
	//�L�X���G 
	if(found && count!=0)	//���@���H�W�q�LP�����| 
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
	//�}output�ɮ� 
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
