/*
 * main.c
 *
 *  Created on: Sep 14, 2015
 *      Author: crims_000
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "hash.h"
#include "linkedList.h"

struct fileStruct{
		int amountWords;
		char words[15][LONGESTWORD];
	};

void checkWordInHash(char *word,FILE* file)
{
	char word2[LONGESTWORD];
	strcpy(word2,word);
	strcat(word2,"\n");
	int x = hash(word2,HASHSIZE);


	fseek(file,sizeof(struct fileStruct)*x,SEEK_SET);

	struct fileStruct data;
	struct fileStruct *dataP = &data;

	fread(dataP,sizeof(struct fileStruct),1,file);

	int y;
	for(y = 0; y < dataP->amountWords; y++)
	{
		if(strcmp(word2,dataP->words[y]) == 0)
			printf("The word could be %s\n",word);
	}
}

//Algorithm found online
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *a, int l, int r, FILE* file)
{
   int i;
   if (l == r)
   {
	   checkWordInHash(a,file);
   }
   else
   {
       for (i = l; i <= r; i++)
       {
          swap((a+l), (a+i));
          permute(a, l+1, r,file);
          swap((a+l), (a+i)); //backtrack
       }
   }
}


int main(int argc,char *argv[])
{
	if(argc != 2)
		printf("Wrong number of arguments\nArguments in format program scrambledword");
	else
	{
		//char word[LONGESTWORD];
		remove("wordlist.txt");
		int x = strlen(argv[1]);
		FILE* file = fopen("library.bin","rb");
		permute(argv[1],0,x-1,file);
		/*fclose(file);
		file = fopen("wordlist.txt","r");
		FILE* file2 = fopen("library.bin","rb");
		while(fgets(word,LONGESTWORD,file) != NULL)
		{
			checkWordInHash(word,file2);
		}*/
		fclose(file);
		//fclose(file2);

	}
	return 0;
}
