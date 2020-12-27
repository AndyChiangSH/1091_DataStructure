//4108056005_DS_HW03_1-2 

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
void postorder(Bptr);	//後續搜尋法 
void generateMax(Bptr); //用後續來產生最大組合 
int MAX(int A,int B);	//回傳最大值 
void findArea(Bptr,int,int); 	//把區間加入Queue
void findMax(Bptr);	//合併區間中最大值
void printfMax(Bptr,int,int,int,int);	//印出區間中最大值
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
	
	fscanf(fin,"%d",&T);	//讀取T 
	for(i=0;i<T;i++)
	{
		printf("No. %d now loading....\n",i+1);
		root=NULL;
		for(j=0;j<MAX_N;j++)
		{
			nArray[j]=0;
		}
		
		fscanf(fin,"%d",&N);	//讀取N 
		for(j=0;j<N;j++)
		{
			fscanf(fin,"%d",&nArray[j]);
		}
		addNode(root,1,N);
		generateMax(root);
				
		fscanf(fin,"%d",&M);	//讀去M 
		for(j=0;j<M;j++)
		{
			int x1,y1,x2,y2;
			fscanf(fin,"\n");
			fscanf(fin,"%d %d %d %d",&x1,&y1,&x2,&y2);
			printfMax(root,x1,y1,x2,y2);
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
	currentNode->difer=(mini+maxi)/2;	//最大最小相加除2=分歧點
	currentNode->left=addNode(currentNode->left,mini,currentNode->difer);	//往左傳(mini,difer) 
	currentNode->right=addNode(currentNode->right,(currentNode->difer)+1,maxi);	//往右傳(difer+1,maxi) 
	
	return currentNode;
}

void postorder(Bptr node)
{
	if(node!=NULL)
	{
		postorder(node->left);
		postorder(node->right);
		if(node->maxi==node->mini)
		{
			printf("node->difer = %d, node->value = %d\n",node->difer,node->value);
		}		
	}	
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

void printfMax(Bptr root,int x1,int y1,int x2,int y2)	//ABC法 
{
	int Ar=0,Bb=0,Bl=0,Br=0,Ba=0,Cl=0,totalMax=0;	//分成ABC三段 
	if(x2<=y1)	//重疊
	{
		//A.right
		collect=createNode(); oper=createNode(); isFirst=1;	//初始化
		findArea(root,x1,x2-1);
		Ar=collect->rightMax;
		free(collect); free(oper);	
		
		//B.both/left/right/alone
		collect=createNode(); oper=createNode(); isFirst=1;	//初始化
		findArea(root,x2,y1);
		Bb=collect->bothMax;
		Bl=collect->leftMax;
		Br=collect->rightMax;
		Ba=collect->alone;
		free(collect); free(oper);
		
		//C.left
		collect=createNode(); oper=createNode(); isFirst=1;	//初始化
		findArea(root,y1+1,y2);
		Cl=collect->leftMax;
		free(collect); free(oper);
			
		totalMax=MAX(Ar+Bb+Cl,MAX(Ar+Bl,MAX(Br+Cl,Ba)));
	}
	else	//不重疊 
	{
		//A.right
		collect=createNode(); oper=createNode(); isFirst=1;	//初始化
		findArea(root,x1,y1);
		Ar=collect->rightMax;
		free(collect); free(oper);	
		
		//B.both
		collect=createNode(); oper=createNode(); isFirst=1;	//初始化
		findArea(root,y1+1,x2-1);
		Bb=collect->bothMax;
		free(collect); free(oper);
		
		//C.left
		collect=createNode(); oper=createNode(); isFirst=1;	//初始化
		findArea(root,x2,y2);
		Cl=collect->leftMax;
		free(collect); free(oper);
		
		totalMax=Ar+Bb+Cl;
	}
	
//	printf("%d\n",totalMax);	//印出範圍中最大值
	fprintf(fout,"%d\n",totalMax);
}

void clearTree(Bptr node)
{
	if(node!=NULL)
	{
		clearTree(node->left);
		clearTree(node->right);
		free(node);
	}
}
