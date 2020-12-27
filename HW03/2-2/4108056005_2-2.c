//4108056005_hw03_2-2 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_M 50

FILE *fin;
FILE *fout;

void init();	//初始化摩斯密碼 
void encoder(char);	//解碼器 
int readFile(int);	//讀檔

struct morse	//每個字母對應的摩斯密碼 
{
	char code[5];
	short int length;
}mc[26];

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
	char wordMorse[200]="";	//word的morseCode 
	
	fscanf(fin,"%s",&word);
	for(j=0;j<strlen(word);j++)
	{
		strcat(wordMorse,mc[word[j]-'A'].code);	//每一個字母轉成摩斯密碼後，接上前面的密碼 
	}

	fscanf(fin,"%d",&M);	//讀取M 
	for(i=0;i<M;i++)	//讀取M個str 
	{
		char str[MAX_M];
		char strMorse[200]="";	//str的morseCode 
		fscanf(fin,"%s",&str);
		for(j=0;j<strlen(str);j++)
		{
			strcat(strMorse,mc[str[j]-'A'].code);	//每一個字母轉成摩斯密碼後，接上前面的密碼 
		}
		
		short int isSamePrefix=0;
		for(j=0;;j++)	//從字串頭開始往後找 
		{
			if(wordMorse[j]!=strMorse[j])	//如果值不一樣，代表沒有prefix 
			{
				break;
			}
			else if(strlen(strMorse)<=j+1 || strlen(wordMorse)<=j+1)	//如果其中一邊已經到底了，還沒有跳出，代表有prefix 
			{				
				isSamePrefix=1;
				break;
			}
		}		
		
		if(strcmp(strMorse,wordMorse)==0)	//完全相同
		{
//			printf("%s is the same as %s.\n",str,word);
			fprintf(fout,"%s is the same as %s.\n",str,word);
		}
		else if(isSamePrefix==1)	//相同prefix
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
