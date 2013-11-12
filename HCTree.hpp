#ifndef HCTREE_HPP
#define HCTREE_HPP

#include "HCNode.hpp"
#include <stdio.h>

typedef struct
{
	HCNODE* root;
	HCNODE* leaves[];
}HCTREE;

void build(HCTREE *, unsigned int[]);
//start by writing one byte per symbol to file, it's slow, but easier to debug
void encode(byte symbol, FILE*);
int decode(FILE*);
#endif
