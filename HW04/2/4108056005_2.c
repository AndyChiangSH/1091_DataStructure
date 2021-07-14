//4108056005_hw04_Q2
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DIAL 10

FILE *fin;

short int dial[MAX_DIAL][MAX_DIAL][MAX_DIAL][MAX_DIAL];	//����A-1�N���z���A1�N����I�A��l��0 
short int bmark[MAX_DIAL][MAX_DIAL][MAX_DIAL][MAX_DIAL];	//�����s�ת��Z�� 

typedef struct		//���c: �K�Ӥ�V
{
	short int d1;
	short int d2;
	short int d3;
	short int d4;
}offsets;
offsets move[8];

typedef struct Qnode* qptr;
struct Qnode	//Queue�`�I
{
	int len;
	short int d1;
	short int d2;
	short int d3;
	short int d4;
	qptr next;
}qnode;
qptr front=NULL,rear=NULL;

void setMove();	//��l�ƤK�ز��ʤ�V 
void inti();	//��l�ư}�C 
qptr createNode(int,short int,short int,short int,short int);	//�إ߷s�`�I 
void addQueue(qptr);	//�[�JQueue 
qptr delQueue();	//�qQueue������ 
void bfs();	//�s�׷j�M 

int main() 
{
	//////////////////////////////////////////////////////////////���ɦW�b�� 
	
	char fin_name[]="test1.txt";
	
	/////////////////////////////////////////////////////////////////////// 
	printf("%s now reading...\n",fin_name);
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}	
	
	setMove();
	inti();
	
	short int start[4];
	short int final[4];
	short int i,N;
	fscanf(fin,"%d %d %d %d",&start[0],&start[1],&start[2],&start[3]);	//Ū�J�_�I 
	fscanf(fin,"%d %d %d %d",&final[0],&final[1],&final[2],&final[3]);	//Ū�J���I 
	dial[final[0]][final[1]][final[2]][final[3]]=1;	//1�N����I
	fscanf(fin,"%d",&N);
	short int forbidden[4];
	for(i=0;i<N;i++)
	{
		fscanf(fin,"%d %d %d %d",&forbidden[0],&forbidden[1],&forbidden[2],&forbidden[3]);
		dial[forbidden[0]][forbidden[1]][forbidden[2]][forbidden[3]]=-1;	//-1�N���z�� 
	}
	
	qptr temp=createNode(0,start[0],start[1],start[2],start[3]);
	addQueue(temp);	//�̤@�}�l�N�_�I�[�JQueue 
	bmark[start[0]][start[1]][start[2]][start[3]]=0;
	bfs();
	
	return 0;
}

void setMove()
{	
	//d1�V�W�� 
	move[0].d1=1;
	move[0].d2=1;
	move[0].d3=0;
	move[0].d4=0;
	
	//d1�V�U�� 
	move[1].d1=-1;
	move[1].d2=-1; 
	move[1].d3=0;
	move[1].d4=0;
	
	//d2�V�W�� 
	move[2].d1=1;
	move[2].d2=1;
	move[2].d3=1;
	move[2].d4=0;
	
	//d2�V�U�� 
	move[3].d1=-1;
	move[3].d2=-1; 
	move[3].d3=-1;
	move[3].d4=0;
	
	//d3�V�W�� 
	move[4].d1=0;
	move[4].d2=1;
	move[4].d3=1;
	move[4].d4=1;
	
	//d3�V�U�� 
	move[5].d1=0;
	move[5].d2=-1; 
	move[5].d3=-1;
	move[5].d4=-1;
	
	//d4�V�W�� 
	move[6].d1=0;
	move[6].d2=0;
	move[6].d3=1;
	move[6].d4=1;
	
	//d4�V�U�� 
	move[7].d1=0;
	move[7].d2=0; 
	move[7].d3=-1;
	move[7].d4=-1;
}

void inti()
{
	int i,j,k,l;
	for(i=0;i<MAX_DIAL;i++)
	{
		for(j=0;j<MAX_DIAL;j++)
		{
			for(k=0;k<MAX_DIAL;k++)
			{
				for(l=0;l<MAX_DIAL;l++)
				{
					dial[i][j][k][l]=0;
					bmark[i][j][k][l]=999;
				}				
			}			
		}		
	}
}

qptr createNode(int len,short int d1,short int d2,short int d3,short int d4)	//���ͷs�`�I(�n�O����) 
{
	qptr temp;
	temp=(qptr)malloc(sizeof(qnode));
	if(!temp)	//�O���餣���� 
	{
		printf("no memory\n");
		exit(1);
	}
	temp->len=len;	//�w�Ʀn��J���� 
	temp->d1=d1;
	temp->d2=d2;
	temp->d3=d3;
	temp->d4=d4;
	temp->next=NULL;
	return temp;
}

void addQueue(qptr node)
{
	if(!front)	//�Ĥ@���[�J 
	{
//		printf("FIRST ADD\n");
		front=node;
		rear=node;	
	}
	else
	{
//		printf("ADD\n");
		rear->next=node;
		rear=node;		
	}	
}

qptr delQueue()
{
//	printf("DELETE\n");
	qptr temp=front;
	if(!front)	//Queue�ŤF 
	{
		return NULL;
	}
	else
	{
		front=front->next;
		return temp;
	}	
}

void bfs()
{
	int nextd1,nextd2,nextd3,nextd4,dir,shortest=0;
	int i,j,k,l;
	short int bfound=0;
	
	while(!bfound)
	{
		qptr current=delQueue();
		if(!current)	//current==NULL�A�N��Queue�ŤF�A�w�g�L���i���F 
		{
			break;
		}
		for(dir=0;dir<8;dir++)
		{
			//����nextd1~nextd4�W�X�d��(0~9) 
			nextd1=(current->d1+move[dir].d1+10)%10;
			nextd2=(current->d2+move[dir].d2+10)%10;
			nextd3=(current->d3+move[dir].d3+10)%10;
			nextd4=(current->d4+move[dir].d4+10)%10;
			if(dial[nextd1][nextd2][nextd3][nextd4]==1)	//�J�W���I�A���X�j�� 
			{
				shortest=current->len+1;
				bfound=1;
				break;
			}
			else if(dial[nextd1][nextd2][nextd3][nextd4]==0)	//�O�Ŧa�A�B�S���L 
			{
				if(current->len+1<bmark[nextd1][nextd2][nextd3][nextd4])	//�p�G�s���Ȥ���p�A�N�л\�W�h 
				{
					bmark[nextd1][nextd2][nextd3][nextd4]=current->len+1;
					qptr temp=createNode(current->len+1,nextd1,nextd2,nextd3,nextd4);
					addQueue(temp);
				}
			}
		}
	} 
	
	if(bfound)
	{
		int d1,d2,d3,d4,pred1,pred2,pred3,pred4;
		printf("%d\n",shortest);
		d1=nextd1;
		d2=nextd2;
		d3=nextd3;
		d4=nextd4;
		offsets step[shortest];
		
		for(i=shortest-1;i>=0;i--)	//�q���I�s�@�����|�^�h
		{
			for(dir=7;dir>=0;dir--)
			{
				pred1=(d1+move[dir].d1+10)%10;
				pred2=(d2+move[dir].d2+10)%10;
				pred3=(d3+move[dir].d3+10)%10;
				pred4=(d4+move[dir].d4+10)%10;
				if(bmark[pred1][pred2][pred3][pred4]==i)	//���ۤv�Ʀr-1����m
				{
					step[i].d1=d1;
					step[i].d2=d2;
					step[i].d3=d3;
					step[i].d4=d4;
					d1=pred1;
					d2=pred2;
					d3=pred3;
					d4=pred4;
					break;
				}
			}
		}
		for(i=0;i<shortest;i++)
		{
			printf("%d%d%d%d\n",step[i].d1,step[i].d2,step[i].d3,step[i].d4);	//���s�b�@�Ӱ}�C���A�̫�Ϥ�V���L 
		}
	}
	else
	{
		printf("Impossible\n");
	}
}
