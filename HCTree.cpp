#include <stdio.h>
#include <stdlib.h>
#include "HCTree.hpp"

/*
typedef struct HCTREE
{
	HCNODE* root;
	symbol symbolTable[MAX_NUM_SYMBOLS];
	void (*build)(HCTREE*, int*);
	void (*encode)(byte symbol, FILE*);
	int (*decode)(FILE*);
}HCTREE;
*/
void build(HCTREE* hcTree, int* counts)
{
	//initialize all leaf pointers as null
	HCNODE* leaves[MAX_NUM_SYMBOLS] = { 0 }; 

	HCNODE* leaf;
	QUEUE queue;
	queue.init();


	//put all leaf nodes into queue and into leaf pointer array
	for(int i; i< MAX_NUM_SYMBOLS; i++)
	{
		leaf = malloc(sizeof(HCNODE));
		queue.push(leaf->init(leaf, counts[i], (byte)i));
		leaves[i] = leaf;
	}

	//create huffing tree
	hcTree->root = reduceQueueToTree(queue);

//	hcTree->leaves = leaves;

	//create symbol table based on huffing tree and leaf vector
	createSymbolTable(hcTree, leaves);
}

/*
 * assuming the tree has already been built, create a compact symbol table
 * so lookup for each leaf is O(1) instead of O(logN)
 */
void createSymbolTable(HCTREE* hcTree, HCNODE* leaves[])
{

}
/*
 * takes a queue and starts creating trees by merging highest priority
 * elements until there is only one element in the queue which is the
 * huffman tree, then returns the pointer to the root of this tree
 */
HCNODE* reduceQueueToTree(QUEUE queue)
{
	HCNODE* c0;
	HCNODE* c1;
	HCNODE* newRoot;

	while(queue.size() > 1)
	{
		newRoot = (HCNODE*)malloc(sizeof(HCNODE));
		c0 = queue.pop();
		c1 = queue.pop();

		newRoot->count = c0->count + c1->count;
		newRoot->symbol = c0->symbol;
		newRoot->c0 = c0;
		c0->parent = newRoot;
		newRoot->c1 = c1;
		c1->parent = newRoot;
		newRoot->parent = 0;

		queue.push(newRoot);
	}
	return queue.pop();
}
//start by writing one byte per symbol to file, it's slow, but easier to debug
void encode(byte symbol, FILE*)
{
}
int decode(FILE*)
{
	return 5;
}
