//4108056005_hw03_2-2 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_M 50

FILE *fin;
FILE *fout;

void init();	//��l�Ƽ����K�X 
void encoder(char);	//�ѽX�� 
int readFile(int);	//Ū��

struct morse	//�C�Ӧr�������������K�X 
{
	char code[5];
	short int length;
}mc[26];

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
	
	int N,M;
	int i,j;	
	char word[MAX_M];
	char wordMorse[200]="";	//word��morseCode 
	
	fscanf(fin,"%s",&word);
	for(j=0;j<strlen(word);j++)
	{
		strcat(wordMorse,mc[word[j]-'A'].code);	//�C�@�Ӧr���ন�����K�X��A���W�e�����K�X 
	}

	fscanf(fin,"%d",&M);	//Ū��M 
	for(i=0;i<M;i++)	//Ū��M��str 
	{
		char str[MAX_M];
		char strMorse[200]="";	//str��morseCode 
		fscanf(fin,"%s",&str);
		for(j=0;j<strlen(str);j++)
		{
			strcat(strMorse,mc[str[j]-'A'].code);	//�C�@�Ӧr���ন�����K�X��A���W�e�����K�X 
		}
		
		short int isSamePrefix=0;
		for(j=0;;j++)	//�q�r���Y�}�l����� 
		{
			if(wordMorse[j]!=strMorse[j])	//�p�G�Ȥ��@�ˡA�N��S��prefix 
			{
				break;
			}
			else if(strlen(strMorse)<=j+1 || strlen(wordMorse)<=j+1)	//�p�G�䤤�@��w�g�쩳�F�A�٨S�����X�A�N��prefix 
			{				
				isSamePrefix=1;
				break;
			}
		}		
		
		if(strcmp(strMorse,wordMorse)==0)	//�����ۦP
		{
//			printf("%s is the same as %s.\n",str,word);
			fprintf(fout,"%s is the same as %s.\n",str,word);
		}
		else if(isSamePrefix==1)	//�ۦPprefix
		{
//			printf("%s has the same prefix as %s.\n",str,word);
			fprintf(fout,"%s has the same prefix as %s.\n",str,word);
		}
		else
		{
//			printf("%s doesn't have the same prefix as %s.\n",str,word);
			fprintf(fout,"%s doesn't have the same prefix as %s.\n",str,word);
		} 
	}
	
	fclose(fin);
	fclose(fout);
}
