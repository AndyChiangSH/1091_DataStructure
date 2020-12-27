//4108056005_hw2_1-3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fin;

int readFile(int num)
{
	//Ū�ɳ��� 
	char fin_name[12]="";
	sprintf(fin_name,"test%d.txt",num);
	printf("%s now reading...\n",fin_name);
	fin=fopen(fin_name,"r");
	if(fin==NULL)
	{
		printf("\nError: Can't find the input file!\n");
		return 0;
	}

	int N,M,i,j,k,input=0;
	fscanf(fin,"%d",&N);	//Ū�JN 
	fscanf(fin,"%d",&M);	//Ū�JM 

	int count[N][N];	//�p��@�y�ܤ��C�ӫR���X�{������ 
	char compare[N],ch;	//�ԭz�̫᭱�᪺����T/L�A����|���Ӹ�enu��� 
	char enu[N];		//�o����إߦC�|�Ϊ��}�C�A����|��compare��� 
	for(i=0; i<N; i++)	//��l�}�C 
	{
		for(j=0; j<N; j++)
		{
			count[i][j]=0;
		}
	}
	for(i=0; i<N; i++)
	{
		fscanf(fin,"%d>",&j);
		while((ch=fgetc(fin))!='=')	//Ū��'='�ԭz���� 
		{
			if(ch!='>')	//Ū��'>'���j�Ʀr
			{
				input=(input*10)+(int)(ch-48);
			}
			else
			{
				count[i][input]++;	//�ֿn�F�l���Ӽ� 
				input=0;
			}
		}
		count[i][input]++;
		input=0;
		fscanf(fin,"%c",&compare[i]);	//Ū�h�̫᪺T/L 
	}
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			count[i][j]=count[i][j]%2;	//���@��i�H����(TT�MLL���v�T���G) 
		}
	}
	//Ū�ɳ������� 
	
	int pos[M];	//�s��C�|���A���X�ӤH�O�F�l 
	short int found=0;
	for(i=0; i<M; i++)	//��l�� 
	{
		pos[i]=i;
	}
	pos[M-1]--;
	while(1)	//���N�|���X
	{
		//�o�����O�ΨӳB�z�C�|���󪺴��� 
		short int change=0;
		for(j=0; j<M; j++)
		{
			if(pos[j]==N-M+j)	//N-M+j�N��Ʀr�쩳���� 
			{
				if(j==0)	//��Ĥ@���F�l�쩳�ɡA�N��Ҧ��i�ೣ�]�L�F�A�����j�� 
				{
					break;
				}
				pos[j-1]++;	//��W�@�ӥ[�@ 
				for(k=j; k<M; k++)
				{
					pos[k]=pos[j-1]+(k-j+1);	//�ç⤧�᪺�Ʀr���K�b�Ĥ@�ӼƦr���� 
				}
				change=1;
				break;
			}
		}
		if(j==0)
		{
			break;
		}
		if(change==0)	//�S���Ʀr�I�쩳�����p�A�̫�@�ӼƦr�[�@ 
		{
			pos[M-1]++;
		}
		//�C�|�������� 
		
		for(i=0; i<N; i++)
		{
			enu[i]='T';
		}
		for(i=0; i<M; i++)
		{
			enu[pos[i]]='L';	//���F�l�]��L 
		}

		short int wrong=0;
		for(i=0; i<N; i++)
		{
			int lnum=0;
			for(j=0; j<M; j++)
			{
				lnum=lnum+count[i][pos[j]];	//�ֿn�F�l���ƶq 
			}
			if(lnum%2==0)	//�����ƭ�L�A���G�ۦP
			{
				if(compare[i]!=enu[i])	//���G�ۤϡA�����D
				{
					wrong=1;
				}
			}
			else	//���_�ƭ�L�A���G�ۤ�
			{
				if(compare[i]==enu[i])	//���G�ۦP�A�����D
				{
					wrong=1;
				}
			}
			if(wrong) //�����~�A�������^while�j��}�Y 
			{
				break;
			}
		}
		if(!wrong)	//�����ԭz�����T 
		{
			found=1;
			break;			
		}
	}

	if(found)	//��X���� 
	{
		printf("test%d:",num);
		for(i=0; i<M; i++)
		{
			printf(" %d",pos[i]);
		}
		printf("\n");
	}
	else
	{
		printf("Wrong input!\n");
	}

	fclose(fin);
	return 0;
}

int main()
{	
	//Ū�ɦb�o��!!!///////////////////////////////////////////////////////////////////////////
	
	readFile(1);	//��J�Ʀr0�N��Ūtest0.txt�A�̦�����
	
	////////////////////////////////////////////////////////////////////////////////////////// 

	return 0;
}
