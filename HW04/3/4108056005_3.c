//4108056005_hw04_Q3
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fin;

void lookMap(char*,int*,int);	//�L�X���v�a�� 
int lookInfo(char*,int*,int);	//��ڶ]�L�C�ӵ���A�ˬd���S�����D�ص����@�� 
int dfs(char*,char*,int*,int,int,int,int,int);	//�`�׷j�M(�u�ƹL) 

int main() 
{
	//////////////////////////////////////////////////////////////���ɦW�b�� 
	
	char fin_name[]="test3.txt";
	
	/////////////////////////////////////////////////////////////////////// 
	printf("%s now reading...\n",fin_name);
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}	
	
	int i,j;
	int N,Vcount,Zcount,Gcount;
	fscanf(fin,"%d %d %d",&Vcount,&Zcount,&Gcount);
	printf("Vcount : %d\n",Vcount);
	printf("Zcount : %d\n",Zcount);
	printf("Gcount : %d\n",Gcount);
	fscanf(fin,"%d",&N);
	int visible[4][N];	//�|�䵡��ݨ쪺�Ǫ��ƶq 
	for(i=0;i<4;i++)
	{
		for(j=0;j<N;j++)
		{
			fscanf(fin,"%d",&visible[i][j]);
		}
	}
	char map[N][N];	//���v�a�� 
	char origin[N][N];	//�����a�ϭ쪬�A�{������ɤ��|�v�T�L 
	fgetc(fin);
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			map[i][j]=fgetc(fin);
			origin[i][j]=map[i][j];
		}
		fgetc(fin);
	}
	
	//���`�׷j�M 
	dfs(&origin[0][0],&map[0][0],&visible[0][0],0,N,Vcount,Zcount,Gcount);

	fclose(fin);
	return 0;
}

void lookMap(char* ptr,int* vis,int n)
{
	//ptr = &map[0][0] 
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%c",*(ptr+(i*n)+j));
		}
		printf("\n");
	}
}

int lookInfo(char* ptr,int* vis,int n)
{
	//ptr = &map[0][0]
	/*�^��0  -> ���@�����u����
	  �^��1 -> �L�׬O�_�w�g�񺡡A�Ҧ��w�g�s���@�������u���O�諸*/ 
	int i,j,x,y,dir;
	for(j=0;j<4;j++)
	{
		for(i=0;i<n;i++)
		{
			short int mirror=0;
			int count=0;
			if(j==0)	//�q�W������ 
			{
				x=-1;
				y=i;
				dir=2;
			}
			else if(j==1)	//�q�U������ 
			{
				x=n;
				y=i;
				dir=0;				
			}
			else if(j==2)	//�q���䵡�� 
			{
				x=i;
				y=-1;
				dir=1;				
			}
			else if(j==3)	//�q�k�䵡�� 
			{
				x=i;
				y=n;
				dir=3;				
			}
			while(1)
			{
				if(dir==0) 	//��V�V�W 
				{
					x--;
					if(*(ptr+(x*n)+y)=='\\')
					{
						dir=3;	//�४ 
						mirror=1;
					}
					else if(*(ptr+(x*n)+y)=='/')
					{
						dir=1;	//��k 
						mirror=1;
					}
				}
				else if(dir==1)	//��V�V�k 
				{
					y++;
					if(*(ptr+(x*n)+y)=='\\')
					{
						dir=2;	//��U 
						mirror=1;
					}
					if(*(ptr+(x*n)+y)=='/')
					{
						dir=0;	//��W 
						mirror=1;
					}
				}
				else if(dir==2)	//��V�V�U 
				{
					x++;
					if(*(ptr+(x*n)+y)=='\\')
					{
						dir=1;	//��k
						mirror=1; 
					}
					if(*(ptr+(x*n)+y)=='/')
					{
						dir=3;	//�४ 
						mirror=1;
					}
				}
				else if(dir==3)	//��V�V�� 
				{
					y--;
					if(*(ptr+(x*n)+y)=='\\')
					{
						dir=0; 	//��W 
						mirror=1;
					}
					if(*(ptr+(x*n)+y)=='/')
					{
						dir=2;	//��U 
						mirror=1;
					}
				}
				
				if(*(ptr+(x*n)+y)=='.')	//���u������A���X 
				{
					break;
				}				
				if(x<0 || x>n-1 || y<0 || y>n-1)	//�W�X�d��N���X�j�� 
				{
					if(*(vis+(j*n)+i)!=count)
					{
						return 0;
					}
					break;
				}
				
				if(mirror==0)	//���q�L��l�A�ݪ����L�͡B�l�尭 
				{
					if(*(ptr+(x*n)+y)=='Z' || *(ptr+(x*n)+y)=='V')
					{
						count++;
					}
				}
				else	//�q�L��l�A�ݪ����L�͡B���� 
				{
					if(*(ptr+(x*n)+y)=='Z' || *(ptr+(x*n)+y)=='G')
					{
						count++;
					}
				}
			}
		}	
	}
	return 1;
}

int time=0;	//�������j���� 
int dfs(char* ori,char* map,int* vis,int x,int n,int Vcount,int Zcount,int Gcount)
{
//	lookMap(map,vis,n);
	/*�^��0 -> �N��o�����H�U���O����
	  �^��1 -> �N��w�g���ѵ��F*/
	while(*(ori+x)!='.')	//��X�U�@���Ů�
	{
		x++;
	}
	if(!lookInfo(map,vis,n))	//�p�G�����A���]���n�A���U���j�F�A�åB���^�h 
	{
		time++;
		return 0;
	}
	if(Vcount==0 && Zcount==0 && Gcount==0)	//�񺡪Ů� 
	{
		printf("time = %d\n",time);
		lookMap(map,vis,n);	//���T�ѵ� 
		return 1;	//���ѵ���^��1�A���ΦA�~���U�h�F 
	}
	else
	{
		if(Vcount>0)	//�p�G�l�尭�٦��� 
		{
			*(map+x)='V';
			if(dfs(ori,map,vis,x+1,n,Vcount-1,Zcount,Gcount))
			{
				return 1;
			}
			else
			{
				*(map+x)='.';	//�^�_�������L
			}				
		}
		if(Zcount>0)	//�p�G�L���٦���  
		{
			*(map+x)='Z';
			if(dfs(ori,map,vis,x+1,n,Vcount,Zcount-1,Gcount))
			{
				return 1;
			}
			else
			{
				*(map+x)='.';	//�^�_�������L 
			}	
		}
		if(Gcount>0)	//�p�G�����٦��� 
		{
			*(map+x)='G';
			if(dfs(ori,map,vis,x+1,n,Vcount,Zcount,Gcount-1))
			{
				return 1;
			}
			else
			{
				*(map+x)='.';	//�^�_�������L
			}	
		}
	}
	return 0;
}
