//4108056005_hw2_1-2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INT 99999999

struct TreeNode		//樹節點 
{
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
}TNode;
struct TreeNode *root=NULL;
struct TreeNode *cNode=NULL;

struct QueueNode	//樹節點組成的Queue 
{
	struct TreeNode *tNode;
	struct QueueNode *next;
}QNode;
struct QueueNode *front=NULL;
struct QueueNode *rear=NULL;

struct MinNode	//存最小值資料的Node 
{
	int minParent;
	int minSelf;
	int minChild;
}MNode;

FILE *fin;

int addQueue(struct TreeNode* node)	//從REAR加入樹節點指標 
{
	struct QueueNode *temp;
	temp=(struct QueueNode*)malloc(sizeof(QNode));
	temp->tNode=node;
	temp->next=NULL;
	if(front)
	{
		rear->next=temp;
		rear=temp;
	}
	else	//第一次加入 
	{
		front=temp;
		rear=temp;
	}
}

struct TreeNode* delQueue()	//從FRONT取出樹節點指標 
{
	struct QueueNode *temp=front;
	struct TreeNode *node;
	if(!temp)
	{
		exit(1);
	}
	else
	{
		node=temp->tNode;
		front=temp->next;
		free(temp);
		return node;
	}
}

struct TreeNode* createNode(int data)	//產生新樹節點(要記憶體+初始) 
{
	struct TreeNode *temp;
	temp=(struct TreeNode*)malloc(sizeof(TNode));
	temp->data=data;	//初始化data值 
	temp->left=NULL;	//初始化左子為NULL 
	temp->right=NULL;	//初始化右子為NULL
	return temp;
}

short dirc=0;	//紀錄往左子還是右子
int insertTree(int data)	//加入樹
{
	struct TreeNode *newNode=NULL;
	if(!root)	//沒有root(第一個節點)
	{
		if(data!=-1)
		{
			newNode=createNode(data);
			root=newNode;
			cNode=newNode;
		}
	}
	else if(dirc==0)	//往左子 
	{
		if(data!=-1)	//不是NULL 
		{
			newNode=createNode(data);
			cNode->left=newNode;
			addQueue(newNode);	//可能是下一個cNode 
		}	
		dirc++;
	}
	else if(dirc==1)	//往右子 
	{
		if(data!=-1)	//不是NULL
		{
			newNode=createNode(data);
			cNode->right=newNode;
			addQueue(newNode);	//可能是下一個cNode
		}
		dirc=0;
		cNode=delQueue(); //將下一個cNode取出 
	}
}

int getMin(int A,int B,int C)	//取三個值中的最小值 
{
	int min=MAX_INT;
	if(A<min)
	{
		min=A;
	}
	if(B<min)
	{
		min=B;
	}
	if(C<min)
	{
		min=C;
	}
	return min;
}

struct MinNode* traverse(struct TreeNode* ptr)	//遞迴找最小花費 
{
	struct MinNode* mptr=(struct MinNode*)malloc(sizeof(MNode));
	
	if(ptr==NULL)	//是NULL
	{
		mptr->minParent=MAX_INT;
		mptr->minSelf=0;
		mptr->minChild=0;
	}
	else	//不是NULL
	{
		struct MinNode* lmptr=traverse(ptr->left);
		struct MinNode* rmptr=traverse(ptr->right);
			
		mptr->minParent=ptr->data+lmptr->minChild+rmptr->minChild;
		mptr->minSelf=getMin((lmptr->minParent+rmptr->minSelf),(lmptr->minSelf+rmptr->minParent),mptr->minParent);
		mptr->minChild=getMin((lmptr->minSelf+rmptr->minSelf),mptr->minParent,MAX_INT);		
	}
	return mptr;	//回傳MNode的節點指標 
}

int readFile(int num)	//num代表檔案號碼 
{
	//讀檔+種樹部分 
	char fin_name[12]="";
	sprintf(fin_name,"test%d.txt",num);
	printf("%s now reading...\n",fin_name);
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}

	int input=0,isNull=0;
	char ch;
	fgetc(fin);
	while((ch=fgetc(fin))!=']')	//讀到']'就結束輸入 
	{
		if(ch!=',')	//讀到','分隔數字或NULL 
		{
			if(ch=='n')
			{
				isNull=1;
			}
			else
			{
				input=(input*10)+(int)(ch-48);
			}	
		}
		else
		{
			if(!isNull)	//輸入不為NULL 
			{
				insertTree(input);
			}
			else	//輸入為NULL
			{
				insertTree(-1);
			}			
			input=0;
			isNull=0;
		}
	}
	if(!isNull)	//輸入不為NULL
	{
		insertTree(input);
	}
	else	//輸入為NULL
	{
		insertTree(-1);
	}
	//讀檔+種樹部分結束
	
	struct MinNode* rptr=traverse(root);
	printf("test%d : %d\n",num,rptr->minSelf);
	
	fclose(fin);
	return 0;
}

int main()
{	
	int i;
//	for(i=1;i<=3;i++)	//樹沒有清乾淨，全部讀會爆掉www 
//		readFile(i);

	//讀檔在這裡!!!///////////////////////////////////////////////////////////////////////////
		
	readFile(1);	//輸入數字0代表讀test0.txt，依此類推 
	
	////////////////////////////////////////////////////////////////////////////////////////// 
	
	return 0;
}
