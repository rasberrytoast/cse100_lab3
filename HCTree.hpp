#ifndef HCTREE_HPP
#define HCTREE_HPP

#define MAX_NUM_SYMBOLS 256
#include "HCNode.hpp"
#include <stdio.h>

typedef unsigned char byte;

typedef struct HCTREE
{
	HCNODE* root;
	//HCNODE* leaves[MAX_NUM_SYMBOLS];
	byte symbolTable[MAX_NUM_SYMBOLS];
	void (*build)(HCTREE*, int*);
	void (*encode)(HCTREE*, byte symbol, FILE*);
	int (*decode)(HCTREE*, byte symbol, FILE*);
	void (*deleteTree)(HCTREE*);
}HCTREE;

typedef struct QUEUE
{
	int size;
	HCNODE* head;
	void (*init)(QUEUE*);
	int (*size)(QUEUE*);
	HCNODE* (*pop)(QUEUE*);
	void (*push)(QUEUE*, HCNODE*);
	void (*deleteAll)(QUEUE*);
}QUEUE;

//for HCTree
void build(HCTREE*, int*);
void encode(HCTREE*, byte symbol, FILE*);
int decode(HCTREE*, byte symbol, FILE*);
void (*deleteTree)(HCTREE*);

//for queue
void (*init)(QUEUE*);
int (*size)(QUEUE*);
HCNODE* (*pop)(QUEUE*);
void (*push)(QUEUE*, HCNODE*);
void (*deleteAll)(QUEUE*);
#endif
