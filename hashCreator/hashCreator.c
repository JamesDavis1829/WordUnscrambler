/*
 * main.c
 *
 *  Created on: Sep 11, 2015
 *      Author: crims_000
 */

#include <stdio.h>
#include <strings.h>
#include "hash.h"
#include "linkedList.h"


HashP createHashFromLinkedList(int ,linkedlistP);
void createHashFile(int longest, HashP table);

int main(int argc,char *argv[])
{
	if(argc != 2)
		printf("\nWrong amount of parameters\nParamteters are: filename.txt");
	else
	{
		linkedlistP list = createListFromFile(argv[1]);
		HashP table = createHashFromLinkedList(HASHSIZE,list);
		int longest = displayStatisticsInt(table);
		createHashFile(longest,table);
		freeList(list);
		freeHash(table);

	}
	return 0;
}

HashP createHashFromLinkedList(int size,linkedlistP list)
{
	HashP table = newHash(size);
	nodeP current = list->head;

	while(current->next != NULL)
	{
		insertHash(table,current->word);
		current = current->next;
	}
	return table;
}

void createHashFile(int longest, HashP table)
{
	struct fileStruct{
		int amountWords;
		char words[15][LONGESTWORD];
	};

	FILE* filepointer = fopen("library.bin","wb");

	int x,y;
	struct fileStruct container;
	struct fileStruct *containerP = &container;

	for(x = 0; x < table->amount; x++)
	{
		y = 0;
		if(table->list[x]->word[0] != '\0')
		{
			HashNodeP current = table->list[x];
			while(current->next != NULL)
			{

				strcpy(containerP->words[y],current->word);
				y++;
				current = current->next;
			}
			containerP->amountWords = y+1;
			strcpy(containerP->words[y],current->word);
		}
		else
		{
			containerP->amountWords = 0;

		}
		fwrite(containerP,sizeof(struct fileStruct),1,filepointer);
	}

}
