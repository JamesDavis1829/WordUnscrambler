/*
 * hash.c
 *
 *  Created on: Sep 11, 2015
 *      Author: crims_000
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define LONGESTWORD 35
#include "linkedList.h"

/*
 * Hash Interface
 */

 struct HashNode{
	struct HashNode *next;
	char word[LONGESTWORD];
};

typedef struct HashNode HashNode;
typedef HashNode *HashNodeP;

struct Hash{
	int amount;
	HashNodeP *list;
};

typedef struct Hash Hash;
typedef struct Hash *HashP;





/*Returns the index of the array after hashing the
 *passed contact
 *Parameter: Contact, and int Size of table
 */
int hash(char* word, int size)
{
	int amount = strlen(word),x,code = 0;

	for(x = 0; x < amount; x++)
	{
		if(x == 0)
			code = code + (int)(word[x] * 900000);
		else
		{
			code = code - (int)(word[x]*x);
		}

	}

	code = code%size;

	return code;
}

/*
 * Returns a pointer to a new empty Hash
 * Parameters: integer indicating desired size of table
 * If memory cannot be allocated, returns a NULL pointer
 */
HashP newHash(int size)
{
	HashP point = (HashP)malloc(sizeof(Hash));
	point->amount = size;
	point->list = (HashNode**)malloc(sizeof(HashNode*)*size);
	int x;
	for(x = 0; x < size; x++)
	{
		point->list[x] = (HashNodeP)malloc(sizeof(HashNode));
		point->list[x]->word[0] = '\0';
		point->list[x]->next = NULL;
	}

	return point;

}

HashNodeP newHashNode(char* word)
{
	HashNodeP node = malloc(sizeof(HashNode));
	node->next = NULL;
	strcpy(node->word,word);
	return node;
}

/*
 * Locates and displays the desired contact from the hash table
 * If entry is not found, display an appropriate message
 * Parameters: hash, first name, last name
 */
void lookupHash(HashP table, char *word)
{
	int place = hash(word,table->amount);
	if(table->list[place]->word[0] == '\0')
	{
		fprintf(stderr,"\nERROR: No word found");
		return;
	}
	else if(strcmp(word,table->list[place]->word) == 0)
	{
		printf("\nThe word %s is in the table",table->list[place]->word);
		return;
	}
	else
	{
		HashNodeP current = table->list[place];
		while(current->next != NULL)
		{
			current = current->next;
			if(strcmp(word,current->word) == 0)
			{
				printf("\nThe word %s is in the table",current->word);
				return;
			}
		}
		fprintf(stderr,"\nERROR: No word found");
		return;
	}
}

/*
 * Creates a new entry for the hash table using provided data
 * Parameters: hash, first name, last name, address, phone, email
 */
void insertHash(HashP table, char *word)
{
	int place = hash(word, table->amount);

	if(table->list[place]->word[0] == '\0')
	{
		strcpy(table->list[place]->word,word);
		return;
	}
	else
	{
		if(table->list[place]->next == NULL)
		{
			table->list[place]->next = newHashNode(word);
		}
		else
		{
			HashNodeP current = table->list[place]->next;
			while(current->next != NULL)
			{
				current = current->next;
			}
			current->next = newHashNode(word);
		}
	}


}

/*
 * Removes the entry containing the matching names
 * Parameters: hash, first name, last name
 */
void removeHash(HashP table, char* word)
{
	int place = hash(word,table->amount);
	if(strcmp(word,table->list[place]->word) == 0)
	{
		HashNodeP temp = table->list[place];
		if(table->list[place]->next == NULL)
		{
			table->list[place]->word[0] = '\0';
			return;
		}
		else
		{
			HashNodeP current = temp, previous = temp;
			while(current->next != NULL)
			{
				previous = current;
				current = current->next;
			}
			strcpy(temp->word, current->word);
			free(current);
			previous->next = NULL;
			return;
		}
	}
	else
	{
		HashNodeP current,previous;
		current = table->list[place];
		while(current->next != NULL)
		{
			previous = current;
			current = current->next;
			if(strcmp(word,current->word) == 0)
			{
				if(current->next == NULL)
				{
					free(current);
					previous->next = NULL;
					return;
				}
				else
				{
					previous->next = current->next;
					free(current);
					return;
				}
			}
		}
	}
}

/*
 * Displays all the entries in the hash table
 * Note: they need not be in any order
 */
void displayHash(HashP table)
{
	printf("\nTable: ");
	int x = 0;
	while(x < table->amount)
	{
		if(table->list[x]->word[0] != '\0')
		{
			printf("\n%s",table->list[x]->word);
			if(table->list[x]->next != NULL)
			{
				HashNodeP current = table->list[x]->next;
				printf(" %s",current->word);
				while(current->next != NULL)
				{
					current = current->next;
					printf(" %s",current->word);
				}
			}
		}
		x++;
	}
}

/*
 * Displays statistics for hash table
 *      Key count
 *      Bucket count (table size)
 *      Used bucket count
 *      Empty bucket count
 *      Collision count
 *      Longest chain length
 *      Average chain length of "used" buckets
 * Parameters: hash
 */
void displayStatisticsHash(HashP table)
{
	int keys = 0,bucket = table->amount,ubucket = 0,ebucket = 0,collision = 0,longest = 0;
	float average = 0.00;
	int chainlength,chainlengths[table->amount],chainbuckets = 0;

	int y;
	for(y = 0; y < table->amount; y++)
	{
		chainlengths[y] = 0;
	}

	int x;
	for(x = 0; x < table->amount; x++)
	{
		if(table->list[x]->word[0] == '\0')
		{
			ebucket++;
		}
		else
		{
			ubucket++;
			keys++;
			if(table->list[x]->next != NULL)
			{
				chainbuckets++;
				keys++;
				collision++;
				chainlength = 2;
				HashNodeP current = table->list[x]->next;
				while(current->next != NULL)
				{
					current = current->next;
					chainlength++;
					keys++;
				}

				chainlengths[x] = chainlength;

				if(chainlength > longest)
				{
					longest = chainlength;
				}
			}
		}
	}

	for(y = 0; y < table->amount; y++)
	{
		average += chainlengths[y];
	}

	if(average != 0)
	{
		average = average / chainbuckets;
	}
	else
	{
		average = 0.00;
	}

	printf("\n\nHash table statistics:      \n");
	printf("Key Count            : %d\n",keys);
	printf("Bucket Count         : %d\n",bucket);
	printf("Used Bucket Count    : %d\n",ubucket);
	printf("Empty Bucket Count   : %d\n",ebucket);
	printf("Collision Count      : %d\n",collision);
	printf("Longest Chain Length : %d\n",longest);
	printf("Average Chain Length : %0.2f\n",average);
}

/*
 * Frees the memory used by this hash
 * Frees all the nodes
 * Parameters: hash
 * Returns NULL
 */
HashP freeHash(HashP table)
{
	int x;
	for(x = 0; x < table->amount; x++)
	{
		if(table->list[x]->next == NULL)
		{
			free(table->list[x]);
		}
		else
		{
			HashNodeP current = table->list[x]->next,previous = table->list[x];
			while(current->next != NULL)
			{
				free(previous);
				previous = current;
				current = current->next;
			}
			free(previous);
			free(current);
		}
	}
	free(table);
	return NULL;
}

int displayStatisticsInt(HashP table)
{
	int keys = 0,bucket = table->amount,ubucket = 0,ebucket = 0,collision = 0,longest = 0;
		float average = 0.00;
		int chainlength,chainlengths[table->amount],chainbuckets = 0;

		int y;
		for(y = 0; y < table->amount; y++)
		{
			chainlengths[y] = 0;
		}

		int x;
		for(x = 0; x < table->amount; x++)
		{
			if(table->list[x]->word[0] == '\0')
			{
				ebucket++;
			}
			else
			{
				ubucket++;
				keys++;
				if(table->list[x]->next != NULL)
				{
					chainbuckets++;
					keys++;
					collision++;
					chainlength = 2;
					HashNodeP current = table->list[x]->next;
					while(current->next != NULL)
					{
						current = current->next;
						chainlength++;
						keys++;
					}

					chainlengths[x] = chainlength;

					if(chainlength > longest)
					{
						longest = chainlength;
					}
				}
			}
		}

		for(y = 0; y < table->amount; y++)
		{
			average += chainlengths[y];
		}

		if(average != 0)
		{
			average = average / chainbuckets;
		}
		else
		{
			average = 0.00;
		}

		printf("\n\nHash table statistics:      \n");
		printf("Key Count            : %d\n",keys);
		printf("Bucket Count         : %d\n",bucket);
		printf("Used Bucket Count    : %d\n",ubucket);
		printf("Empty Bucket Count   : %d\n",ebucket);
		printf("Collision Count      : %d\n",collision);
		printf("Longest Chain Length : %d\n",longest);
		printf("Average Chain Length : %0.2f\n",average);

		return longest;
}


