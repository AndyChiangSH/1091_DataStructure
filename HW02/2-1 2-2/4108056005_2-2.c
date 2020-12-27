//4108056005_hw2_2-2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int length=0;
char AtoZ[]={' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

FILE *fin;

typedef struct platform	//雙向環狀鏈結節點 
{
	struct platform *llink;	//指向左節點 
	int data;
	struct platform *rlink;	//指向右節點 
}platform_node;
typedef platform_node *platform_ptr;	//雙向環狀鏈結節點的指標 
platform_ptr head=NULL,current=NULL,ptr=NULL;

void insert(int n)	//插入節點在head的右邊 
{
	platform_ptr ptr;
	ptr=(platform_ptr)malloc(sizeof(platform_node));
	ptr->data=n%27;
	if(!head)	//沒有head 
	{
		head=ptr;
		ptr->llink=ptr;
		ptr->rlink=ptr;
	}
	else	//插入新節點在head和head->rlink之間 
	{
		current=head->rlink;
		ptr->llink=current->llink;
		ptr->rlink=current;
		current->llink->rlink=ptr;
		current->llink=ptr;
	}
}

void traverse()		//印出整個鏈結 
{
	if(!head)
	{
		printf("此為空字串，無法印出\n");
	}
	else
	{
		if(AtoZ[head->data]==' ')	//空白看不到，改成印'#'比較好辨識 
		{
			printf("# ");
		}
		else
		{
			printf("%c ",AtoZ[head->data]);
		}
		current=head->rlink;
		while(current!=head)
		{
			if(AtoZ[current->data]==' ')
			{
				printf("# ");
			}
			else
			{
				printf("%c ",AtoZ[current->data]);
			}
			current=current->rlink;
		}
		printf("\n");
	}
}

int abs(int n)	//取絕對值 
{
	if(n<0)
	{
		return -n;
	}
	return n;
}

int lengthCount(platform_ptr nptr,char input)	//計算轉換字母的cost 
{
	int count=0;
	
	count=(input-'A'+1)-(nptr->data);
	if(count>13)	//距離若大於13，則逆方向走會更近 
	{
		count=count-27;
	}
	else if(count<-13)	//距離若小於-13，則逆方向走會更近 
	{
		count=count+27;
	}
	
	return count;
}

void move(char input)
{
	//min代表最小轉換字母的cost，min_step代表移動月台的cost，limit代表往左/右找幾個月台 
	int min=99999,min_step=99999,i,limit=10;
	platform_ptr temp=NULL;
	
	int count=lengthCount(ptr,input);	//跟自己比 
	if(abs(count)<abs(min)+abs(min_step))
	{
		min=count;
		min_step=0;
		temp=ptr;
	}
	
	platform_ptr lrptr=ptr;
	for(i=-1;i>=-limit;i--)	//跟左邊limit個比
	{
		int lcount=lengthCount(lrptr->llink,input); 
		if(abs(lcount)+abs(i)<abs(min)+abs(min_step))
		{
			min=lcount;
			min_step=i;
			temp=lrptr->llink;
		}
		lrptr=lrptr->llink;
	}

	lrptr=ptr;
	for(i=1;i<=limit;i++)	//跟右邊limit個比 
	{
		int rcount=lengthCount(lrptr->rlink,input);
		if(abs(rcount)+abs(i)<abs(min)+abs(min_step))
		{
			min=rcount;
			min_step=i;
			temp=lrptr->rlink;
		}
		lrptr=lrptr->rlink;	
	}
	
	if(min_step>0)	//正為往右 
	{
		for(i=0;i<abs(min_step);i++)
		{
			printf(">");
		}
	}
	else	//負為往左 
	{
		for(i=0;i<abs(min_step);i++)
		{
			printf("<");
		}		
	}
	
	if(min>0)	//正為'+' 
	{
		for(i=0;i<abs(min);i++)
		{
			printf("+");
		}
	}
	else	//負為'-' 
	{
		for(i=0;i<abs(min);i++)
		{
			printf("-");
		}		
	}	
	printf(".");

	length=length+abs(min)+abs(min_step)+1;	//+1是加'.'的cost 
	temp->data=(input-'A'+1);
	ptr=temp;
}

int main()
{
	int i;
	for(i=0;i<20;i++)	//產生20個" "的月台 
	{
		insert(0);
	}
	ptr=head;
	
	//讀檔在這裡!!!///////////////////////////////////////////////////////////////////////////

	char fin_name[]="test1.txt";
	
	////////////////////////////////////////////////////////////////////////////////////////// 	
	
	printf("%s now reading...\n",fin_name);
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}
	
	char ch;
	while((ch=fgetc(fin))!=EOF)
	{
		if(ch==' ')	//讀到' '，轉成ASCII碼中'A'的上一位，也就是'@' 
		{
			ch='@';
		}
		move(ch);
	}		
	printf("\nlength = %d\n",length);
	
	fclose(fin);
	return 0;
}
//測資總和 : 2655 94.38%
