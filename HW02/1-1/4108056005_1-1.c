//4108056005_hw2_1-1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	temp->data=data;
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
		if(data!=-1)	//NULL 
		{
			newNode=createNode(data);
			cNode->left=newNode;
			addQueue(newNode);	//�i��O�U�@��cNode 
		}
		dirc++;
	}
	else if(dirc==1)	//���k�l 
	{
		if(data!=-1)	//NULL 
		{
			newNode=createNode(data);
			cNode->right=newNode;
			addQueue(newNode);	//�i��O�U�@��cNode
		}
		dirc=0;
		cNode=delQueue(); //�N�U�@��cNode���X 
	}
}

int bNum=0;	//�N��M���� 
int traverse(struct TreeNode* ptr)
{
	if(ptr==NULL)	//NULL�^��0 
	{
		return 0;
	}
	
	int l=traverse(ptr->left),r=traverse(ptr->right);	// ���(postorder)���X 
	if(l==1 || r==1)	//l �M r �u�n�䤤�@�Ӭ� 1 -> �\�A�^�� -1 
	{
		bNum++;
		return -1;
	}
	else if(l==-1 || r==-1)	//l �M r �u�n�䤤�@�Ӭ� -1 -> �^�� 0 
	{
		return 0;
	}
	else	//l==0 && r==0
	{
		if(ptr==root)	//ROOT�S�Q�O�@��A�\! 
		{
			bNum++;
			return 0;
		}
		else	//��l�`�I�h�^�� 1 
		{
			return 1;
		}
	}
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
	
	bNum=0;
	traverse(root);
	printf("test%d : %d\n\n",num,bNum);
	
	fclose(fin);
	return 0;
}

int main()
{	
	int i;
//	for(i=1;i<=3;i++)	//����Ū�|�z�� 
//		readFile(i);

	//Ū�ɦb�o��!!!///////////////////////////////////////////////////////////////////////////
		
	readFile(1);	//��J�Ʀr0�N��Ūtest0.txt�A�̦����� 
	
	////////////////////////////////////////////////////////////////////////////////////////// 
	
	return 0;
}
