//4108056005_hw04_Q1
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fin;

typedef struct headNode *hptr;
typedef struct listNode *lptr;

typedef struct headNode		//�ܼƪ����Y
{
	char var[2];
	lptr next;
	lptr top;
	char func[2];
	short int visited;
}headNode;
typedef struct listNode		//��{�������ܼ� 
{
	hptr rel;	//�|���V��L�ܼƪ����Y 
	lptr next;
}listNode;

lptr createNode();	//�гy�s��listNode 
int runPath(hptr);	//�ն]�ݬݦ��S���Φ��j�� 
void printPath(hptr);	//�L�X�i�}�� 

int main() 
{
	//////////////////////////////////////////////////////////////���ɦW�b�� 
	
	char fin_name[]="test5.txt";
	
	/////////////////////////////////////////////////////////////////////// 
	printf("%s now reading...\n",fin_name);
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}	
	
	int i,j;
	int N,M;
	
	fscanf(fin,"%d",&N);	//Ū��N 
	headNode headArr[N];	//�ܼƼ��Y���@���}�C 
	for(i=0;i<N;i++)	//�NN���ܼƦs�J�}�C�� 
	{
		headArr[i].top=NULL;
		headArr[i].next=NULL;
		headArr[i].visited=0;
		char var[2];
		fscanf(fin,"%s ",&var);
		strcpy(headArr[i].var,var);
	}
	
	fscanf(fin,"%d",&M);	//Ū��M 
	for(i=0;i<M;i++)		//�NM����{���নlist 
	{
		char defVar[2];
		char func[2];
		int index=0;
		fscanf(fin,"%s = %s ( ",&defVar,&func);
		
		for(j=0;j<N;j++)
		{
			if(!strcmp(headArr[j].var,defVar))	//��X�w�q�ܼƪ����ޭȡA�s�bindex 
			{
				strcpy(headArr[j].func,func);
				index=j;
				break;
			} 
		}
		
		char relVar[2]="";
		while(1)
		{
			fscanf(fin,"%s ",&relVar);
			if(!strcmp(relVar,")"))	//�r��ۦP�^��0�AŪ�� ')' �N���� 
			{
				break;
			}
			else	//�����U�@���ܼ� 
			{	
				for(j=0;j<N;j++)
				{
					if(!strcmp(headArr[j].var,relVar))	//��X�����ܼƪ����ޭ� 
					{
						lptr temp=createNode();
						temp->rel=&headArr[j];	//�s������ܼƪ����Y 
						if(headArr[index].top==NULL)
						{
							headArr[index].next=temp;
						}
						else
						{
							headArr[index].top->next=temp;
						}
						headArr[index].top=temp;
						break;
					} 
				}
				strcpy(relVar,"");
			}
		}
	}
	
	short int noSolu=0;
	for(i=0;i<N;i++)
	{
		if(runPath(&headArr[i]))	//�p�G�^��1�A�h�N��ӹϧΦ��j�� 
		{
			noSolu=1;
			break;
		}
	}
	
	if(noSolu)
	{
		printf("No solution.\n");
	}
	else
	{
		for(i=0;i<N;i++)
		{
			printf("%s -> ",headArr[i].var);
			printPath(&headArr[i]);
			printf("\n");
		}		
	}
	
	fclose(fin);
	return 0;
}

lptr createNode()	//���ͷs��`�I(�n�O����) 
{
	lptr temp;
	temp=(lptr)malloc(sizeof(listNode));
	temp->next=NULL;
	return temp;
}

int runPath(hptr node)
{
	if(node->visited)
	{
		return 1;
	}
	if(node->next!=NULL)
	{
		lptr temp;
		for(temp=node->next;temp;temp=temp->next)
		{
			node->visited=1;
			if(runPath(temp->rel))	//�p�G�W�@�Ӧ^��1�A�h�L�����1�^�h 
			{
				return 1;
			}
			node->visited=0;
		}
	}
	return 0;
}

void printPath(hptr node)
{
	if(node->next==NULL)
	{
		printf("%s ",node->var);	//�]�쩳�ɡA�L�X���ܼ� 
	}
	else
	{
		lptr temp;
		printf("%s ( ",node->func);
		for(temp=node->next;temp;temp=temp->next)
		{
			printPath(temp->rel);
		}
		printf(") ");
	}
}
