/*
 * linkedList.c

 *
 *  Created on: Sep 12, 2015
 *      Author: crims_000
 */

#define WORDLENGTH 35
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

struct node{
	char word[WORDLENGTH];
	struct node *next;
};

struct linkedlist{
	struct node *head;
};

typedef struct node node;
typedef node *nodeP;

typedef struct linkedlist linkedlist;
typedef linkedlist *linkedlistP;


nodeP createNode(char* word)
{
	nodeP newNode = malloc(sizeof(node));
	strcpy(newNode->word,word);
	newNode->next = NULL;
	return newNode;
}

linkedlistP createList(char* word)
{
	linkedlistP list = malloc(sizeof(linkedlist));
	list->head = createNode(word);
	return list;
}

void addNode(linkedlistP list,char* word)
{
	nodeP current = list->head;
	while(current->next != NULL)
	{
		current = current->next;
	}
	current->next = createNode(word);
}

void freeList(linkedlistP list)
{
	nodeP current,temp;
	current = list->head;
	while(current->next != NULL)
	{
		temp = current;
		temp = temp->next;
		free(current);
		current = temp;
	}
	free(current);
	free(list->head);
	return;

}

void printList(linkedlistP list)
{
	printf("\n\nThe list of words: ");
	nodeP current = list->head;
	while(current->next != NULL)
	{
		printf("\n%s",current->word);
		current = current->next;
	}
	return;
}

linkedlistP createListFromFile(char* name)
{
	FILE* file = fopen(name,"r");
	char words[WORDLENGTH];
	int count = 0;
	linkedlistP list;

	while(fgets(words,WORDLENGTH,file) != NULL)
	{
		if(count == 0)
			list = createList(words);
		else
			addNode(list,words);
		count = count+1;
	}

	return list;
}

