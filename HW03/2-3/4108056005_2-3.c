//4108056005_hw03_2-3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_M 20
#define MAX_LN 100000

FILE *fin;
FILE *fout;

struct morse	//每個字母對應的摩斯密碼 
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

struct QueueNode	//動點組成的Queue
{
	dptr dnode;
	long long sum;
	struct QueueNode* next;
}QNode;
typedef struct QueueNode* Qptr;
Qptr front=NULL,rear=NULL;

void init();	//初始化摩斯密碼 
void encoder(char);	//解碼器 
int readFile(int);	//讀檔
dptr createNode();	//建立新節點
dptr addNode(dptr,char);	//加入新字到字典中 
void postorder(dptr);	//後序表示法 
int addQueue(dptr,long long);	//加入Queue 
Qptr delQueue();	//取出Queue
long long movePoint(char);	//移動所有動點(存在Queue中) 
int qlength();	//計算從front到rear的距離，當QUEUE為空(front和rear都為NULL)，則回傳0 

int main()
{
	init();
	
	//讀檔在這<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
	
	readFile(1);	//readFile(1)代表讀取test1.txt，依此類推
	
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
	//讀檔部分 
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
	fscanf(fin,"%s",&morseSeq);	//讀取摩斯密碼 
	
	fscanf(fin,"%d",&N);	//讀取N
	for(i=0;i<N;i++)	//讀取N個str
	{
		char str[MAX_M];
		char strMorse[100]="";	//str的morseCode
		fscanf(fin,"%s",&str);
		for(j=0;j<strlen(str);j++)
		{
			strcat(strMorse,mc[str[j]-'A'].code);	//每一個字母轉成摩斯密碼後，接上前面的密碼 
		}
		
		dptr current=root;
		for(j=0;j<strlen(strMorse);j++)
		{
			current=addNode(current,strMorse[j]);	//將每個單字輸入進字典中對應的位置 
		}
		current->num++;
	}

	long long totalSum=0;	//紀錄組合數總和
	addQueue(root,1);
	for(i=0;i<strlen(morseSeq);i++)	//跑動點 
	{
		totalSum=movePoint(morseSeq[i]);
	}
	printf("test%d: %lld\n",num,totalSum);
	fprintf(fout,"test%d: %lld\n",num,totalSum);
	
	fclose(fin);
	fclose(fout);
}
dptr createNode()	//產生新樹節點(要記憶體) 
{
	dptr temp;
	temp=(dptr)malloc(sizeof(dnode));
	temp->num=0;		//初始數量為零(代表沒有字在這個節點上) 
	temp->left=NULL;	//初始化左子為NULL 
	temp->right=NULL;	//初始化右子為NULL
	return temp;
}
dptr addNode(dptr current,char ch)
{
	if(ch=='.')	//往左 
	{
		if(current->left==NULL)	//此節點尚未走過 
		{
			current->left=createNode();
			current=current->left;
		}
		else
		{
			current=current->left;
		}
	}
	else if(ch=='-')	//往右
	{
		if(current->right==NULL)//此節點尚未走過 
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
int addQueue(dptr node,long long sum)	//從REAR加入樹節點指標 
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
	else	//第一次加入 
	{
		front=temp;
		rear=temp;
	}
}
Qptr delQueue()	//從FRONT取出樹節點指標 
{
	Qptr temp=front;
	Qptr node=(Qptr)malloc(sizeof(QNode));	//因為如果沒有要記憶體，底下把temp給free掉，資料就會不見??
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
	int ql=qlength();	//從front到rear的距離(未加入新節點前queue的長度)
	
	for(i=0;i<ql;i++)
	{
		Qptr temp=delQueue();
		if(ch=='.')	//往左
		{
			temp->dnode=temp->dnode->left;
		}
		else if(ch=='-')	//往右
		{
			temp->dnode=temp->dnode->right;
		}
		else
		{
			printf("ERROR!\n");
			exit(1);
		}
		if(temp->dnode!=NULL)	//如果該點存在 
		{
			if(temp->dnode->num!=0)		//如果該點存在單字 
			{
				if(!isMerge)	//如果還沒有其他節點要合併
				{
					isMerge=1;
				}
				mergeSum=(long long)mergeSum+(long long)((temp->sum)*(temp->dnode->num));	//合併值=合併值+(該點的累積值*該點的數量) 
			}
			addQueue(temp->dnode,temp->sum);	//繼續往下跑的動點
		}
		free(temp);	//temp用不到，可以free掉了
	}
	if(isMerge)	//需要合併
	{
		addQueue(root,mergeSum);	//回到根結點的動點(合併後) 	
	}
	return mergeSum;	//回傳該點的mergeSum(累積到目前合理的可能數)
}
int qlength()
{
	if(front==NULL && front==NULL)	//如果QUEUE為空，則回傳0
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
