//4108056005_hw2_1-2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INT 99999999

struct TreeNode		//��`�I 
{
	int data;
	struct TreeNode *left;
	struct TreeNode *right;
}TNode;
struct TreeNode *root=NULL;
struct TreeNode *cNode=NULL;

struct QueueNode	//��`�I�զ���Queue 
{
	struct TreeNode *tNode;
	struct QueueNode *next;
}QNode;
struct QueueNode *front=NULL;
struct QueueNode *rear=NULL;

struct MinNode	//�s�̤p�ȸ�ƪ�Node 
{
	int minParent;
	int minSelf;
	int minChild;
}MNode;

FILE *fin;

int addQueue(struct TreeNode* node)	//�qREAR�[�J��`�I���� 
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
	else	//�Ĥ@���[�J 
	{
		front=temp;
		rear=temp;
	}
}

struct TreeNode* delQueue()	//�qFRONT���X��`�I���� 
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

struct TreeNode* createNode(int data)	//���ͷs��`�I(�n�O����+��l) 
{
	struct TreeNode *temp;
	temp=(struct TreeNode*)malloc(sizeof(TNode));
	temp->data=data;	//��l��data�� 
	temp->left=NULL;	//��l�ƥ��l��NULL 
	temp->right=NULL;	//��l�ƥk�l��NULL
	return temp;
}

short dirc=0;	//���������l�٬O�k�l
int insertTree(int data)	//�[�J��
{
	struct TreeNode *newNode=NULL;
	if(!root)	//�S��root(�Ĥ@�Ӹ`�I)
	{
		if(data!=-1)
		{
			newNode=createNode(data);
			root=newNode;
			cNode=newNode;
		}
	}
	else if(dirc==0)	//�����l 
	{
		if(data!=-1)	//���ONULL 
		{
			newNode=createNode(data);
			cNode->left=newNode;
			addQueue(newNode);	//�i��O�U�@��cNode 
		}	
		dirc++;
	}
	else if(dirc==1)	//���k�l 
	{
		if(data!=-1)	//���ONULL
		{
			newNode=createNode(data);
			cNode->right=newNode;
			addQueue(newNode);	//�i��O�U�@��cNode
		}
		dirc=0;
		cNode=delQueue(); //�N�U�@��cNode���X 
	}
}

int getMin(int A,int B,int C)	//���T�ӭȤ����̤p�� 
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

struct MinNode* traverse(struct TreeNode* ptr)	//���j��̤p��O 
{
	struct MinNode* mptr=(struct MinNode*)malloc(sizeof(MNode));
	
	if(ptr==NULL)	//�ONULL
	{
		mptr->minParent=MAX_INT;
		mptr->minSelf=0;
		mptr->minChild=0;
	}
	else	//���ONULL
	{
		struct MinNode* lmptr=traverse(ptr->left);
		struct MinNode* rmptr=traverse(ptr->right);
			
		mptr->minParent=ptr->data+lmptr->minChild+rmptr->minChild;
		mptr->minSelf=getMin((lmptr->minParent+rmptr->minSelf),(lmptr->minSelf+rmptr->minParent),mptr->minParent);
		mptr->minChild=getMin((lmptr->minSelf+rmptr->minSelf),mptr->minParent,MAX_INT);		
	}
	return mptr;	//�^��MNode���`�I���� 
}

int readFile(int num)	//num�N���ɮ׸��X 
{
	//Ū��+�ؾ𳡤� 
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
	while((ch=fgetc(fin))!=']')	//Ū��']'�N������J 
	{
		if(ch!=',')	//Ū��','���j�Ʀr��NULL 
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
			if(!isNull)	//��J����NULL 
			{
				insertTree(input);
			}
			else	//��J��NULL
			{
				insertTree(-1);
			}			
			input=0;
			isNull=0;
		}
	}
	if(!isNull)	//��J����NULL
	{
		insertTree(input);
	}
	else	//��J��NULL
	{
		insertTree(-1);
	}
	//Ū��+�ؾ𳡤�����
	
	struct MinNode* rptr=traverse(root);
	printf("test%d : %d\n",num,rptr->minSelf);
	
	fclose(fin);
	return 0;
}

int main()
{	
	int i;
//	for(i=1;i<=3;i++)	//��S���M���b�A����Ū�|�z��www 
//		readFile(i);

	//Ū�ɦb�o��!!!///////////////////////////////////////////////////////////////////////////
		
	readFile(1);	//��J�Ʀr0�N��Ūtest0.txt�A�̦����� 
	
	////////////////////////////////////////////////////////////////////////////////////////// 
	
	return 0;
}
