//4108056005_hw2_2-1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fin;

char AtoZ[]={' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

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
	else
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
		printf("%c ",AtoZ[head->data]);
		current=head->rlink;
		while(current!=head)
		{
			printf("%c ",AtoZ[current->data]);
			current=current->rlink;
		}
		printf("\n");
	}
}

int translate(char input)
{
	if(input=='>')
	{
		ptr=ptr->rlink;
	}
	else if(input=='<')
	{
		ptr=ptr->llink;
	}
	else if(input=='+')
	{
		ptr->data=(ptr->data+1)%27;
	}
	else if(input=='-')
	{
		ptr->data=(ptr->data-1);
		if(ptr->data<0)
		{
			ptr->data=27+ptr->data;
		}
	}
	else if(input=='.')
	{
		printf("%c",AtoZ[ptr->data]);
	}
	else
	{
		printf("WTF??\n");
		return 0;
	}
	return 0;
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
	
	char fin_name[]="ans1.txt";
	
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
		translate(ch);
	}		
	printf("\n");

//	traverse();
	
	fclose(fin);
	return 0;
}
