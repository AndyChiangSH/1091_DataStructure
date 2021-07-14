//4108056005_hw2_2-2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int length=0;
char AtoZ[]={' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

FILE *fin;

typedef struct platform	//���V�����쵲�`�I 
{
	struct platform *llink;	//���V���`�I 
	int data;
	struct platform *rlink;	//���V�k�`�I 
}platform_node;
typedef platform_node *platform_ptr;	//���V�����쵲�`�I������ 
platform_ptr head=NULL,current=NULL,ptr=NULL;

void insert(int n)	//���J�`�I�bhead���k�� 
{
	platform_ptr ptr;
	ptr=(platform_ptr)malloc(sizeof(platform_node));
	ptr->data=n%27;
	if(!head)	//�S��head 
	{
		head=ptr;
		ptr->llink=ptr;
		ptr->rlink=ptr;
	}
	else	//���J�s�`�I�bhead�Mhead->rlink���� 
	{
		current=head->rlink;
		ptr->llink=current->llink;
		ptr->rlink=current;
		current->llink->rlink=ptr;
		current->llink=ptr;
	}
}

void traverse()		//�L�X����쵲 
{
	if(!head)
	{
		printf("�����Ŧr��A�L�k�L�X\n");
	}
	else
	{
		if(AtoZ[head->data]==' ')	//�ťլݤ���A�令�L'#'����n���� 
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

int abs(int n)	//������� 
{
	if(n<0)
	{
		return -n;
	}
	return n;
}

int lengthCount(platform_ptr nptr,char input)	//�p���ഫ�r����cost 
{
	int count=0;
	
	count=(input-'A'+1)-(nptr->data);
	if(count>13)	//�Z���Y�j��13�A�h�f��V���|��� 
	{
		count=count-27;
	}
	else if(count<-13)	//�Z���Y�p��-13�A�h�f��V���|��� 
	{
		count=count+27;
	}
	
	return count;
}

void move(char input)
{
	//min�N��̤p�ഫ�r����cost�Amin_step�N���ʤ�x��cost�Alimit�N����/�k��X�Ӥ�x 
	int min=99999,min_step=99999,i,limit=10;
	platform_ptr temp=NULL;
	
	int count=lengthCount(ptr,input);	//��ۤv�� 
	if(abs(count)<abs(min)+abs(min_step))
	{
		min=count;
		min_step=0;
		temp=ptr;
	}
	
	platform_ptr lrptr=ptr;
	for(i=-1;i>=-limit;i--)	//����limit�Ӥ�
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
	for(i=1;i<=limit;i++)	//��k��limit�Ӥ� 
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
	
	if(min_step>0)	//�������k 
	{
		for(i=0;i<abs(min_step);i++)
		{
			printf(">");
		}
	}
	else	//�t������ 
	{
		for(i=0;i<abs(min_step);i++)
		{
			printf("<");
		}		
	}
	
	if(min>0)	//����'+' 
	{
		for(i=0;i<abs(min);i++)
		{
			printf("+");
		}
	}
	else	//�t��'-' 
	{
		for(i=0;i<abs(min);i++)
		{
			printf("-");
		}		
	}	
	printf(".");

	length=length+abs(min)+abs(min_step)+1;	//+1�O�['.'��cost 
	temp->data=(input-'A'+1);
	ptr=temp;
}

int main()
{
	int i;
	for(i=0;i<20;i++)	//����20��" "����x 
	{
		insert(0);
	}
	ptr=head;
	
	//Ū�ɦb�o��!!!///////////////////////////////////////////////////////////////////////////

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
		if(ch==' ')	//Ū��' '�A�নASCII�X��'A'���W�@��A�]�N�O'@' 
		{
			ch='@';
		}
		move(ch);
	}		
	printf("\nlength = %d\n",length);
	
	fclose(fin);
	return 0;
}
//�����`�M : 2655 94.38%
