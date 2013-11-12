#ifndef HCTREE_HPP
#define HCTREE_HPP

#include "HCNode.hpp"
#include <stdio.h>

typedef unsigned char byte;

typedef struct HCTREE
{
	HCNODE* root;
	HCNODE* leaves[];
	void (*build)(HCTREE*, int*);
	void (*encode)(byte symbol, FILE*);
	int (*decode)(FILE*);
}HCTREE;

void build(HCTREE*, int*);
//start by writing one byte per symbol to file, it's slow, but easier to debug
void encode(byte symbol, FILE*);
int decode(FILE*);
#endif
