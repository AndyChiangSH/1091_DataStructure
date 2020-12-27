//4108056005_DS_HW03_1-1

#include <stdio.h>
#include <stdlib.h>
#define MAX_N 500000

int nArray[MAX_N];

FILE *fin;
FILE *fout;

struct BSTNode
{
	int value;	//存葉節點的對應值 
	int difer;	//存葉節點的順序值 or 其他節點的分歧值 
	int maxi;	//區間最大值 
	int mini;	//區間最小值 
	struct BSTNode *left;	//左子 
	struct BSTNode *right;	//右子 
	int bothMax;	//整段的最大值 
	int leftMax;	//從左邊數來的最大值 
	int rightMax;	//從右邊數來的最大值 
	int alone;		//不與兩端相接的最大值 
}TNode;
typedef struct BSTNode *Bptr;
Bptr root=NULL;

int readFile(int);	//讀檔 
Bptr createNode();	//產生新樹節點(要記憶體)
Bptr addNode(Bptr,int,int);	//建立半分二元搜尋樹 
void generateMax(Bptr); //用後續來產生最大組合 
int MAX(int A,int B);	//回傳最大值 
void findArea(Bptr,int,int); 	//把區間加入Queue
void findMax(Bptr);	//合併區間中最大值
void printfMax(Bptr,int,int);	//印出區間中最大值
void modify(Bptr,int,int); //修改Ix的值
void clearTree(Bptr);	//清空樹 

short int isFirst=1;
Bptr collect=NULL;	//存全部解
Bptr oper=NULL;	//跟right做運算

int main()
{
	//讀檔在這<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
	
	readFile(1);	//readFile(1)代表讀取test1.txt，依此類推 
	
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
	
	printf("END of the test!\n");
	return 0;
} 

int readFile(int num)
{
	//讀檔部分 
	char fin_name[12]="";
	char fout_name[15]="";
	sprintf(fin_name,"test%d.txt",num);
	sprintf(fout_name,"output%d.txt",num);
	printf("%s now reading...\n",fin_name);
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}
	fout=fopen(fout_name,"w");
	if(fout==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}
	
	int T,N,M;
	int i,j;
	
	fscanf(fin,"%d",&T);
	for(i=0;i<T;i++)
	{
		printf("No. %d now loading....\n",i+1);
		root=NULL;
		for(j=0;j<MAX_N;j++)
		{
			nArray[j]=0;
		}
		
		fscanf(fin,"%d",&N);	//讀取N 
		for(j=0;j<N;j++)	//讀取N個數字 
		{
			fscanf(fin,"%d",&nArray[j]);
		}
		addNode(root,1,N);
		generateMax(root);
		
		fscanf(fin,"%d",&M);	//讀取M 
		for(j=0;j<M;j++)	//讀取M個數字 
		{
			char com;
			int x,y;
			fscanf(fin,"\n");
			fscanf(fin,"%c %d %d",&com,&x,&y);	//讀取指令加上一對數字 
			if(com=='P')	//印出區間最大值 
			{
				isFirst=1;	//初始化
				collect=createNode();
				oper=createNode();
				
				printfMax(root,x,y);
				
				free(collect);
				free(oper);
			}
			else if(com=='M')	//修改特定值 
			{
				modify(root,x,y);
			}
			else
			{
				printf("ERROR!\n");
				return 0;
			}
		}
		clearTree(root);
	}
	
	fclose(fin);
	fclose(fout);
	return 0;
}

Bptr createNode()	//產生新樹節點(要記憶體) 
{
	Bptr temp;
	temp=(Bptr)malloc(sizeof(TNode));
	temp->difer=-1;
	temp->left=NULL;	//初始化左子為NULL 
	temp->right=NULL;	//初始化右子為NULL
	temp->bothMax=0;
	temp->leftMax=0;
	temp->rightMax=0;
	temp->alone=0;
	return temp;
}

Bptr addNode(Bptr currentNode,int mini,int maxi)
{
	currentNode=createNode();
	currentNode->maxi=maxi;
	currentNode->mini=mini;
	if(maxi==mini)	//葉節點 
	{
		currentNode->value=nArray[maxi-1];
		currentNode->difer=maxi;
		return currentNode;
	}
	else if(root==NULL)	//根節點 
	{
		root=currentNode;
	}
	else{}
	currentNode->difer=(mini+maxi)/2;	//最大最小相加除2=分歧點	
	currentNode->left=addNode(currentNode->left,mini,currentNode->difer);	//往左傳(mini,difer) 
	currentNode->right=addNode(currentNode->right,(currentNode->difer)+1,maxi);	//往右傳(difer+1,maxi) 
	
	return currentNode;
}

int MAX(int A,int B)
{
	if(A>B)
	{
		return A;
	}
	return B;
}

void generateMax(Bptr currentNode)
{
	if(currentNode!=NULL)
	{
		generateMax(currentNode->left);
		generateMax(currentNode->right);
		if(currentNode->maxi==currentNode->mini)	//葉節點 
		{
			currentNode->bothMax=currentNode->value;
			currentNode->leftMax=currentNode->value;
			currentNode->rightMax=currentNode->value;
			currentNode->alone=currentNode->value;
		}
		else
		{
			currentNode->bothMax=currentNode->left->bothMax+currentNode->right->bothMax;
			currentNode->leftMax=MAX(currentNode->left->bothMax+currentNode->right->leftMax,currentNode->left->leftMax);
			currentNode->rightMax=MAX(currentNode->left->rightMax+currentNode->right->bothMax,currentNode->right->rightMax);
			currentNode->alone=MAX(currentNode->left->rightMax+currentNode->right->leftMax,MAX(currentNode->left->alone,currentNode->right->alone));	
		}	
	}	
}

void findArea(Bptr node,int low,int high)
{
	if(node!=NULL)
	{
		if(low<=node->mini && high>=node->maxi)	//葉節點或已經包含全部的範圍 
		{
			findMax(node);
		}
		else
		{
			if(low<=node->difer)	//可以往左找 
			{
				findArea(node->left,low,high);
			}
			if(high>node->difer)	//可以往右找 
			{
				findArea(node->right,low,high);
			}			
		}
	}	
}

void findMax(Bptr right)
{	
	if(isFirst)	//第一次
	{
		isFirst=0;

		oper->bothMax=right->bothMax;
		oper->leftMax=right->leftMax;
		oper->rightMax=right->rightMax;
		oper->alone=right->alone;
		
		collect->bothMax=right->bothMax;
		collect->leftMax=right->leftMax;
		collect->rightMax=right->rightMax;
		collect->alone=right->alone;				
	} 
	else
	{
		//取最大值CURRENT 
		collect->bothMax=oper->bothMax+right->bothMax;
		collect->leftMax=MAX(oper->bothMax+right->leftMax,oper->leftMax);
		collect->rightMax=MAX(oper->rightMax+right->bothMax,right->rightMax);
		collect->alone=MAX(oper->rightMax+right->leftMax,MAX(oper->alone,right->alone));		

		//為了下一次運算，讓OPER=CURRENT
		oper->bothMax=collect->bothMax;
		oper->leftMax=collect->leftMax;
		oper->rightMax=collect->rightMax;
		oper->alone=collect->alone;			
	}
}

void printfMax(Bptr root,int low,int high)
{
	findArea(root,low,high);	//找範圍
	int max=MAX(collect->bothMax,MAX(collect->leftMax,MAX(collect->rightMax,collect->alone)));
//	printf("%d\n",max);	//印出範圍中最大值
	fprintf(fout,"%d\n",max);
}

void modify(Bptr currentNode,int x,int y)
{
	if(currentNode!=NULL)
	{
		if(x<=currentNode->difer)	//小於等於往左 
		{
			modify(currentNode->left,x,y);
		}
		else	//大於往右 
		{
			modify(currentNode->right,x,y);
		}
		//一路從葉節點往根節點做回去 
		if(currentNode->maxi==currentNode->mini)	//葉節點 
		{
			currentNode->value=y;
			currentNode->bothMax=currentNode->value;
			currentNode->leftMax=currentNode->value;
			currentNode->rightMax=currentNode->value;
			currentNode->alone=currentNode->value;			
		}
		else
		{
			currentNode->bothMax=currentNode->left->bothMax+currentNode->right->bothMax;
			currentNode->leftMax=MAX(currentNode->left->bothMax+currentNode->right->leftMax,currentNode->left->leftMax);
			currentNode->rightMax=MAX(currentNode->left->rightMax+currentNode->right->bothMax,currentNode->right->rightMax);
			currentNode->alone=MAX(currentNode->left->rightMax+currentNode->right->leftMax,MAX(currentNode->left->alone,currentNode->right->alone));	
		}		
	}
}

void clearTree(Bptr node)
{
	if(node!=NULL)
	{
		clearTree(node->left);
		clearTree(node->right);
		free(node);	//清掉記憶體空間 
	}
}
