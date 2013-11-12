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
	byte symbolEncodedAsZero;
	byte symbolTable[MAX_NUM_SYMBOLS];
	void (*build)(HCTREE*, int*);
	void (*encode)(byte symbol, FILE*);
	int (*decode)(FILE*);
}HCTREE;

void build(HCTREE*, int*);
//start by writing one byte per symbol to file, it's slow, but easier to debug
void encode(byte symbol, FILE*);
int decode(FILE*);
#endif
