//4108056005_DS_HW03_1-2 

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
void postorder(Bptr);	//����j�M�k 
void generateMax(Bptr); //�Ϋ���Ӳ��ͳ̤j�զX 
int MAX(int A,int B);	//�^�ǳ̤j�� 
void findArea(Bptr,int,int); 	//��϶��[�JQueue
void findMax(Bptr);	//�X�ְ϶����̤j��
void printfMax(Bptr,int,int,int,int);	//�L�X�϶����̤j��
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
	
	fscanf(fin,"%d",&T);	//Ū��T 
	for(i=0;i<T;i++)
	{
		printf("No. %d now loading....\n",i+1);
		root=NULL;
		for(j=0;j<MAX_N;j++)
		{
			nArray[j]=0;
		}
		
		fscanf(fin,"%d",&N);	//Ū��N 
		for(j=0;j<N;j++)
		{
			fscanf(fin,"%d",&nArray[j]);
		}
		addNode(root,1,N);
		generateMax(root);
				
		fscanf(fin,"%d",&M);	//Ū�hM 
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
	currentNode->difer=(mini+maxi)/2;	//�̤j�̤p�ۥ[��2=���[�I
	currentNode->left=addNode(currentNode->left,mini,currentNode->difer);	//������(mini,difer) 
	currentNode->right=addNode(currentNode->right,(currentNode->difer)+1,maxi);	//���k��(difer+1,maxi) 
	
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

void printfMax(Bptr root,int x1,int y1,int x2,int y2)	//ABC�k 
{
	int Ar=0,Bb=0,Bl=0,Br=0,Ba=0,Cl=0,totalMax=0;	//����ABC�T�q 
	if(x2<=y1)	//���|
	{
		//A.right
		collect=createNode(); oper=createNode(); isFirst=1;	//��l��
		findArea(root,x1,x2-1);
		Ar=collect->rightMax;
		free(collect); free(oper);	
		
		//B.both/left/right/alone
		collect=createNode(); oper=createNode(); isFirst=1;	//��l��
		findArea(root,x2,y1);
		Bb=collect->bothMax;
		Bl=collect->leftMax;
		Br=collect->rightMax;
		Ba=collect->alone;
		free(collect); free(oper);
		
		//C.left
		collect=createNode(); oper=createNode(); isFirst=1;	//��l��
		findArea(root,y1+1,y2);
		Cl=collect->leftMax;
		free(collect); free(oper);
			
		totalMax=MAX(Ar+Bb+Cl,MAX(Ar+Bl,MAX(Br+Cl,Ba)));
	}
	else	//�����| 
	{
		//A.right
		collect=createNode(); oper=createNode(); isFirst=1;	//��l��
		findArea(root,x1,y1);
		Ar=collect->rightMax;
		free(collect); free(oper);	
		
		//B.both
		collect=createNode(); oper=createNode(); isFirst=1;	//��l��
		findArea(root,y1+1,x2-1);
		Bb=collect->bothMax;
		free(collect); free(oper);
		
		//C.left
		collect=createNode(); oper=createNode(); isFirst=1;	//��l��
		findArea(root,x2,y2);
		Cl=collect->leftMax;
		free(collect); free(oper);
		
		totalMax=Ar+Bb+Cl;
	}
	
//	printf("%d\n",totalMax);	//�L�X�d�򤤳̤j��
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
