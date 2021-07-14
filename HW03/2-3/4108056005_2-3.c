//4108056005_hw03_2-3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_M 20
#define MAX_LN 100000

FILE *fin;
FILE *fout;

struct morse	//�C�Ӧr�������������K�X 
{
	char code[5];
	short int length;
}mc[26];

struct dicTree
{
	int num;
	struct dicTree *left;
	struct dicTree *right;
}dnode;
typedef struct dicTree *dptr;
dptr root=NULL;

struct QueueNode	//���I�զ���Queue
{
	dptr dnode;
	long long sum;
	struct QueueNode* next;
}QNode;
typedef struct QueueNode* Qptr;
Qptr front=NULL,rear=NULL;

void init();	//��l�Ƽ����K�X 
void encoder(char);	//�ѽX�� 
int readFile(int);	//Ū��
dptr createNode();	//�إ߷s�`�I
dptr addNode(dptr,char);	//�[�J�s�r��r�夤 
void postorder(dptr);	//��Ǫ�ܪk 
int addQueue(dptr,long long);	//�[�JQueue 
Qptr delQueue();	//���XQueue
long long movePoint(char);	//���ʩҦ����I(�s�bQueue��) 
int qlength();	//�p��qfront��rear���Z���A��QUEUE����(front�Mrear����NULL)�A�h�^��0 

int main()
{
	init();
	
	//Ū�ɦb�o<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
	
	readFile(1);	//readFile(1)�N��Ū��test1.txt�A�̦�����
	
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
	
	printf("-----END of the test-----\n");
	return 0;
} 
void init()
{
	strcpy(mc[0].code,".-");	//A
	mc[0].length=2;
	strcpy(mc[1].code,"-...");	//B
	mc[1].length=4;
	strcpy(mc[2].code,"-.-.");	//C
	mc[2].length=4;
	strcpy(mc[3].code,"-..");	//D
	mc[3].length=3;
	strcpy(mc[4].code,".");		//E
	mc[4].length=1;
	strcpy(mc[5].code,"..-.");	//F
	mc[5].length=4;
	strcpy(mc[6].code,"--.");	//G
	mc[6].length=3;
	strcpy(mc[7].code,"....");	//H
	mc[7].length=4;
	strcpy(mc[8].code,"..");	//I
	mc[8].length=2;
	strcpy(mc[9].code,".---");	//J
	mc[9].length=4;
	strcpy(mc[10].code,"-.-");	//K
	mc[10].length=3;
	strcpy(mc[11].code,".-..");	//L
	mc[11].length=4;
	strcpy(mc[12].code,"--");	//M
	mc[12].length=2;
	strcpy(mc[13].code,"-.");	//N
	mc[13].length=2;
	strcpy(mc[14].code,"---");	//O
	mc[14].length=3;
	strcpy(mc[15].code,".--.");	//P
	mc[15].length=4;
	strcpy(mc[16].code,"--.-");	//Q
	mc[16].length=4;
	strcpy(mc[17].code,".-.");	//R
	mc[17].length=3;
	strcpy(mc[18].code,"...");	//S
	mc[18].length=3;
	strcpy(mc[19].code,"-");	//T
	mc[19].length=1;
	strcpy(mc[20].code,"..-");	//U
	mc[20].length=3;
	strcpy(mc[21].code,"...-");	//V
	mc[21].length=4;
	strcpy(mc[22].code,".--");	//W
	mc[22].length=3;
	strcpy(mc[23].code,"-..-");	//X
	mc[23].length=4;
	strcpy(mc[24].code,"-.--");	//Y
	mc[24].length=4;
	strcpy(mc[25].code,"--..");	//Z
	mc[25].length=4;
}
void encoder(char ch)
{
	printf("%c = %s\n",ch,mc[ch-'A']);
}
int readFile(int num)
{
	//Ū�ɳ��� 
	char fin_name[12]="";
	char fout_name[15]="";
	sprintf(fin_name,"test%d.txt",num);
	sprintf(fout_name,"myoutput%d.txt",num);
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
	
	int N;
	int i,j;	
	char morseSeq[MAX_LN];
	
	root=createNode();
	fscanf(fin,"%s",&morseSeq);	//Ū�������K�X 
	
	fscanf(fin,"%d",&N);	//Ū��N
	for(i=0;i<N;i++)	//Ū��N��str
	{
		char str[MAX_M];
		char strMorse[100]="";	//str��morseCode
		fscanf(fin,"%s",&str);
		for(j=0;j<strlen(str);j++)
		{
			strcat(strMorse,mc[str[j]-'A'].code);	//�C�@�Ӧr���ন�����K�X��A���W�e�����K�X 
		}
		
		dptr current=root;
		for(j=0;j<strlen(strMorse);j++)
		{
			current=addNode(current,strMorse[j]);	//�N�C�ӳ�r��J�i�r�夤��������m 
		}
		current->num++;
	}

	long long totalSum=0;	//�����զX���`�M
	addQueue(root,1);
	for(i=0;i<strlen(morseSeq);i++)	//�]���I 
	{
		totalSum=movePoint(morseSeq[i]);
	}
	printf("test%d: %lld\n",num,totalSum);
	fprintf(fout,"test%d: %lld\n",num,totalSum);
	
	fclose(fin);
	fclose(fout);
}
dptr createNode()	//���ͷs��`�I(�n�O����) 
{
	dptr temp;
	temp=(dptr)malloc(sizeof(dnode));
	temp->num=0;		//��l�ƶq���s(�N��S���r�b�o�Ӹ`�I�W) 
	temp->left=NULL;	//��l�ƥ��l��NULL 
	temp->right=NULL;	//��l�ƥk�l��NULL
	return temp;
}
dptr addNode(dptr current,char ch)
{
	if(ch=='.')	//���� 
	{
		if(current->left==NULL)	//���`�I�|�����L 
		{
			current->left=createNode();
			current=current->left;
		}
		else
		{
			current=current->left;
		}
	}
	else if(ch=='-')	//���k
	{
		if(current->right==NULL)//���`�I�|�����L 
		{
			current->right=createNode();
			current=current->right;
		}
		else
		{
			current=current->right;
		}		
	}
	else
	{
		printf("ERROR!\n");
		exit(1);
	}
	return current;
}
void postorder(dptr node)
{
	if(node!=NULL)
	{
		postorder(node->left);
		postorder(node->right);
		if(node->num>0)
		{
			printf("num = %d\n",node->num);	
		}	
	}	
}
int addQueue(dptr node,long long sum)	//�qREAR�[�J��`�I���� 
{
	Qptr temp;
	temp=(Qptr)malloc(sizeof(QNode));
	temp->dnode=node;
	temp->sum=sum;
	temp->next=NULL;
	if(rear && front)
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
Qptr delQueue()	//�qFRONT���X��`�I���� 
{
	Qptr temp=front;
	Qptr node=(Qptr)malloc(sizeof(QNode));	//�]���p�G�S���n�O����A���U��temp��free���A��ƴN�|����??
	if(front==NULL)
	{
		printf("EMPTY\n");
		exit(1);
	}
	else
	{
		node->dnode=temp->dnode;
		node->sum=temp->sum;
		if(front==rear)
		{
			front=NULL;
			rear=NULL;
		}
		else
		{
			front=temp->next;
		}
		free(temp);
		return node;
	}
}
long long movePoint(char ch)
{		
	short int isMerge=0;
	long long mergeSum=0;
	int i;
	int ql=qlength();	//�qfront��rear���Z��(���[�J�s�`�I�equeue������)
	
	for(i=0;i<ql;i++)
	{
		Qptr temp=delQueue();
		if(ch=='.')	//����
		{
			temp->dnode=temp->dnode->left;
		}
		else if(ch=='-')	//���k
		{
			temp->dnode=temp->dnode->right;
		}
		else
		{
			printf("ERROR!\n");
			exit(1);
		}
		if(temp->dnode!=NULL)	//�p�G���I�s�b 
		{
			if(temp->dnode->num!=0)		//�p�G���I�s�b��r 
			{
				if(!isMerge)	//�p�G�٨S����L�`�I�n�X��
				{
					isMerge=1;
				}
				mergeSum=(long long)mergeSum+(long long)((temp->sum)*(temp->dnode->num));	//�X�֭�=�X�֭�+(���I���ֿn��*���I���ƶq) 
			}
			addQueue(temp->dnode,temp->sum);	//�~�򩹤U�]�����I
		}
		free(temp);	//temp�Τ���A�i�Hfree���F
	}
	if(isMerge)	//�ݭn�X��
	{
		addQueue(root,mergeSum);	//�^��ڵ��I�����I(�X�֫�) 	
	}
	return mergeSum;	//�^�Ǹ��I��mergeSum(�ֿn��ثe�X�z���i���)
}
int qlength()
{
	if(front==NULL && front==NULL)	//�p�GQUEUE���šA�h�^��0
	{
		return 0;
	}
	
	int length=1;
	Qptr ptr;
	for(ptr=front;ptr!=rear;ptr=ptr->next)
	{
		length++;
	}
	return length;
}
