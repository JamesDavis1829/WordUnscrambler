/*
 * linkedList.h
 *
 *  Created on: Sep 12, 2015
 *      Author: crims_000
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#define WORDLENGTH 35

struct node{
	char word[WORDLENGTH];
	struct node *next;
};

struct linkedlist{
	struct node *head;
};

typedef struct node node;
typedef node* nodeP;

typedef struct linkedlist linkedlist;
typedef linkedlist* linkedlistP;

void addNode(linkedlistP, char*);

linkedlistP createList(char*);

nodeP createNode(char*);

linkedlistP freeList(linkedlistP);

linkedlistP createListFromFile(char*);

void printList(linkedlistP);

#endif /* LINKEDLIST_H_ */
