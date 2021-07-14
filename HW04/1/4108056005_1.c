//4108056005_hw04_Q1
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fin;

typedef struct headNode *hptr;
typedef struct listNode *lptr;

typedef struct headNode		//變數的標頭
{
	char var[2];
	lptr next;
	lptr top;
	char func[2];
	short int visited;
}headNode;
typedef struct listNode		//方程式內的變數 
{
	hptr rel;	//會指向其他變數的標頭 
	lptr next;
}listNode;

lptr createNode();	//創造新的listNode 
int runPath(hptr);	//試跑看看有沒有形成迴圈 
void printPath(hptr);	//印出展開式 

int main() 
{
	//////////////////////////////////////////////////////////////改檔名在此 
	
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
	
	fscanf(fin,"%d",&N);	//讀取N 
	headNode headArr[N];	//變數標頭的一維陣列 
	for(i=0;i<N;i++)	//將N個變數存入陣列中 
	{
		headArr[i].top=NULL;
		headArr[i].next=NULL;
		headArr[i].visited=0;
		char var[2];
		fscanf(fin,"%s ",&var);
		strcpy(headArr[i].var,var);
	}
	
	fscanf(fin,"%d",&M);	//讀取M 
	for(i=0;i<M;i++)		//將M筆方程式轉成list 
	{
		char defVar[2];
		char func[2];
		int index=0;
		fscanf(fin,"%s = %s ( ",&defVar,&func);
		
		for(j=0;j<N;j++)
		{
			if(!strcmp(headArr[j].var,defVar))	//找出定義變數的索引值，存在index 
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
			if(!strcmp(relVar,")"))	//字串相同回傳0，讀到 ')' 代表結束 
			{
				break;
			}
			else	//換成下一個變數 
			{	
				for(j=0;j<N;j++)
				{
					if(!strcmp(headArr[j].var,relVar))	//找出相關變數的索引值 
					{
						lptr temp=createNode();
						temp->rel=&headArr[j];	//連到相關變數的標頭 
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
		if(runPath(&headArr[i]))	//如果回傳1，則代表該圖形成迴圈 
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

lptr createNode()	//產生新樹節點(要記憶體) 
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
			if(runPath(temp->rel))	//如果上一個回傳1，則無條件傳1回去 
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
		printf("%s ",node->var);	//跑到底時，印出該變數 
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
