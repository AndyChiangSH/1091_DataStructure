//4108056005_hw2_1-1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	temp->data=data;
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
		if(data!=-1)	//NULL 
		{
			newNode=createNode(data);
			cNode->left=newNode;
			addQueue(newNode);	//可能是下一個cNode 
		}
		dirc++;
	}
	else if(dirc==1)	//往右子 
	{
		if(data!=-1)	//NULL 
		{
			newNode=createNode(data);
			cNode->right=newNode;
			addQueue(newNode);	//可能是下一個cNode
		}
		dirc=0;
		cNode=delQueue(); //將下一個cNode取出 
	}
}

int bNum=0;	//代表碉堡數 
int traverse(struct TreeNode* ptr)
{
	if(ptr==NULL)	//NULL回傳0 
	{
		return 0;
	}
	
	int l=traverse(ptr->left),r=traverse(ptr->right);	// 後序(postorder)走訪 
	if(l==1 || r==1)	//l 和 r 只要其中一個為 1 -> 蓋，回傳 -1 
	{
		bNum++;
		return -1;
	}
	else if(l==-1 || r==-1)	//l 和 r 只要其中一個為 -1 -> 回傳 0 
	{
		return 0;
	}
	else	//l==0 && r==0
	{
		if(ptr==root)	//ROOT沒被保護到，蓋! 
		{
			bNum++;
			return 0;
		}
		else	//其餘節點則回傳 1 
		{
			return 1;
		}
	}
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
	
	bNum=0;
	traverse(root);
	printf("test%d : %d\n\n",num,bNum);
	
	fclose(fin);
	return 0;
}

int main()
{	
	int i;
//	for(i=1;i<=3;i++)	//全部讀會爆掉 
//		readFile(i);

	//讀檔在這裡!!!///////////////////////////////////////////////////////////////////////////
		
	readFile(1);	//輸入數字0代表讀test0.txt，依此類推 
	
	////////////////////////////////////////////////////////////////////////////////////////// 
	
	return 0;
}
