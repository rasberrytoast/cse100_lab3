#include <stdio.h>
#include <stdlib.h>
#include "HCNode.hpp"


void printHCNode(HCNODE* inputNode)
{
	printf("count:%d, symbol:%08x, c0:%p, c1:%p\n", inputNode->count, \
			inputNode->symbol, (void *)inputNode->c0, \
			(void*)inputNode->c1);
}

HCNODE* hasGreaterPriority(HCNODE* a, HCNODE* b)
{
	if(a->count > b->count)
	{
		return a;
	}
	else if(b->count > a->count)
	{
		return b;
	}
	else if(a->symbol < b->symbol)
	{
		return a;
	}
	else if(b->symbol > a->symbol)
	{
		return b;
	}
	else
	{
		perror("comparing two nodes of same symbol and count");
		exit(EXIT_FAILURE);
	}

}
