/*
 * hash.h
 *
 *  Created on: Sep 11, 2015
 *      Author: crims_000
 */

#ifndef HASH_H_
#define HASH_H_
#define LONGESTWORD 35
#define HASHSIZE 98317

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
typedef Hash *HashP;

typedef struct HashNode HashNode;
typedef HashNode *HashNodeP;

void displayHash(HashP);

void displayStatisticsHash(HashP);

HashP freeHash(HashP);

int hash(char*, int);

void insertHash(HashP,char*);

void lookupHash(HashP,char*);

HashP newHash(int);

HashNodeP newHashNode(char*);

void removeHash(HashP,char*);

HashP createHashFromFile(int size, FILE* file);

int displayStatisticsInt(HashP);

#endif /* HASH_H_ */
