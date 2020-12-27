//4108056005_DS_HW03_1-1

#include <stdio.h>
#include <stdlib.h>
#define MAX_N 500000

int nArray[MAX_N];

FILE *fin;
FILE *fout;

struct BSTNode
{
	int value;	//�s���`�I�������� 
	int difer;	//�s���`�I�����ǭ� or ��L�`�I�����[�� 
	int maxi;	//�϶��̤j�� 
	int mini;	//�϶��̤p�� 
	struct BSTNode *left;	//���l 
	struct BSTNode *right;	//�k�l 
	int bothMax;	//��q���̤j�� 
	int leftMax;	//�q����ƨӪ��̤j�� 
	int rightMax;	//�q�k��ƨӪ��̤j�� 
	int alone;		//���P��ݬ۱����̤j�� 
}TNode;
typedef struct BSTNode *Bptr;
Bptr root=NULL;

int readFile(int);	//Ū�� 
Bptr createNode();	//���ͷs��`�I(�n�O����)
Bptr addNode(Bptr,int,int);	//�إߥb���G���j�M�� 
void generateMax(Bptr); //�Ϋ���Ӳ��ͳ̤j�զX 
int MAX(int A,int B);	//�^�ǳ̤j�� 
void findArea(Bptr,int,int); 	//��϶��[�JQueue
void findMax(Bptr);	//�X�ְ϶����̤j��
void printfMax(Bptr,int,int);	//�L�X�϶����̤j��
void modify(Bptr,int,int); //�ק�Ix����
void clearTree(Bptr);	//�M�ž� 

short int isFirst=1;
Bptr collect=NULL;	//�s������
Bptr oper=NULL;	//��right���B��

int main()
{
	//Ū�ɦb�o<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
	
	readFile(1);	//readFile(1)�N��Ū��test1.txt�A�̦����� 
	
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
	
	printf("END of the test!\n");
	return 0;
} 

int readFile(int num)
{
	//Ū�ɳ��� 
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
		
		fscanf(fin,"%d",&N);	//Ū��N 
		for(j=0;j<N;j++)	//Ū��N�ӼƦr 
		{
			fscanf(fin,"%d",&nArray[j]);
		}
		addNode(root,1,N);
		generateMax(root);
		
		fscanf(fin,"%d",&M);	//Ū��M 
		for(j=0;j<M;j++)	//Ū��M�ӼƦr 
		{
			char com;
			int x,y;
			fscanf(fin,"\n");
			fscanf(fin,"%c %d %d",&com,&x,&y);	//Ū�����O�[�W�@��Ʀr 
			if(com=='P')	//�L�X�϶��̤j�� 
			{
				isFirst=1;	//��l��
				collect=createNode();
				oper=createNode();
				
				printfMax(root,x,y);
				
				free(collect);
				free(oper);
			}
			else if(com=='M')	//�ק�S�w�� 
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

Bptr createNode()	//���ͷs��`�I(�n�O����) 
{
	Bptr temp;
	temp=(Bptr)malloc(sizeof(TNode));
	temp->difer=-1;
	temp->left=NULL;	//��l�ƥ��l��NULL 
	temp->right=NULL;	//��l�ƥk�l��NULL
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
	if(maxi==mini)	//���`�I 
	{
		currentNode->value=nArray[maxi-1];
		currentNode->difer=maxi;
		return currentNode;
	}
	else if(root==NULL)	//�ڸ`�I 
	{
		root=currentNode;
	}
	else{}
	currentNode->difer=(mini+maxi)/2;	//�̤j�̤p�ۥ[��2=���[�I	
	currentNode->left=addNode(currentNode->left,mini,currentNode->difer);	//������(mini,difer) 
	currentNode->right=addNode(currentNode->right,(currentNode->difer)+1,maxi);	//���k��(difer+1,maxi) 
	
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
		if(currentNode->maxi==currentNode->mini)	//���`�I 
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
		if(low<=node->mini && high>=node->maxi)	//���`�I�Τw�g�]�t�������d�� 
		{
			findMax(node);
		}
		else
		{
			if(low<=node->difer)	//�i�H������ 
			{
				findArea(node->left,low,high);
			}
			if(high>node->difer)	//�i�H���k�� 
			{
				findArea(node->right,low,high);
			}			
		}
	}	
}

void findMax(Bptr right)
{	
	if(isFirst)	//�Ĥ@��
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
		//���̤j��CURRENT 
		collect->bothMax=oper->bothMax+right->bothMax;
		collect->leftMax=MAX(oper->bothMax+right->leftMax,oper->leftMax);
		collect->rightMax=MAX(oper->rightMax+right->bothMax,right->rightMax);
		collect->alone=MAX(oper->rightMax+right->leftMax,MAX(oper->alone,right->alone));		

		//���F�U�@���B��A��OPER=CURRENT
		oper->bothMax=collect->bothMax;
		oper->leftMax=collect->leftMax;
		oper->rightMax=collect->rightMax;
		oper->alone=collect->alone;			
	}
}

void printfMax(Bptr root,int low,int high)
{
	findArea(root,low,high);	//��d��
	int max=MAX(collect->bothMax,MAX(collect->leftMax,MAX(collect->rightMax,collect->alone)));
//	printf("%d\n",max);	//�L�X�d�򤤳̤j��
	fprintf(fout,"%d\n",max);
}

void modify(Bptr currentNode,int x,int y)
{
	if(currentNode!=NULL)
	{
		if(x<=currentNode->difer)	//�p�󵥩󩹥� 
		{
			modify(currentNode->left,x,y);
		}
		else	//�j�󩹥k 
		{
			modify(currentNode->right,x,y);
		}
		//�@���q���`�I���ڸ`�I���^�h 
		if(currentNode->maxi==currentNode->mini)	//���`�I 
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
		free(node);	//�M���O����Ŷ� 
	}
}
