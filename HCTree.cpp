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
	queue.initQueue(&queue);


	//put all leaf nodes into queue and into leaf pointer array
	for(int i = 0; i< MAX_NUM_SYMBOLS; i++)
	{
		leaf = (HCNODE*)malloc(sizeof(HCNODE));
		leaf->initNode(leaf, counts[i], (byte)i);
		queue.push(&queue, leaf);
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
	for(int i = 0; i< MAX_NUM_SYMBOLS; i++)
	{
		if(leaves[i])
		{
			hcTree->symbolTable[i] = 0;
			while(leaves[i]->parent)
			{
				if(leaves[i] == leaves[i]->parent->c1)
				{
					hcTree->symbolTable[i] <<= 1;
					hcTree->symbolTable[i] |= 0x1;
				}
				else if(leaves[i] == leaves[i]->parent->c0)
				{
					hcTree->symbolTable[i] <<= 1;
				}
				else
				{
					perror("indicated parent exists, but this node is not the \
							right or left child");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
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
	HCNODE* returnRoot;

	while(queue.size(&queue) > 1)
	{
		newRoot = (HCNODE*)malloc(sizeof(HCNODE));
		c0 = queue.pop(&queue);
		c1 = queue.pop(&queue);

		newRoot->count = c0->count + c1->count;
		newRoot->symbol = c0->symbol;
		newRoot->c0 = c0;
		c0->parent = newRoot;
		newRoot->c1 = c1;
		c1->parent = newRoot;
		newRoot->parent = 0;

		queue.push(&queue, newRoot);
	}
	returnRoot = queue.pop(&queue);
	queue.deleteAll(&queue);
	return returnRoot;
}
//start by writing one byte per symbol to file, it's slow, but easier to debug
void encode(HCTREE* hcTree, byte symbol, FILE* fpOut)
{
	fputc(hcTree->symbolTable[symbol], fpOut);
	//fwrite(hcTree->symbolTable[symbol], fpOut); 
}
byte decode(HCTREE* hcTree, byte c, FILE* fpOut)
{
	//since we are only handling ascii, we can just use the character to 
	//start decoding
	HCNODE* cursor = hcTree->root;

	//tree is a complete bst so, as long as node has a child, it isn't a leaf
	while(cursor->c0)
	{
		if(c & 0x1)
		{
			cursor = cursor->c1;
		}
		else
		{
			cursor = cursor->c0;
		}
		c >>= 1;
	}
	fputs((const char*)cursor->symbol, fpOut);
	return cursor->symbol;
}

void deleteTree(HCTREE* hcTree)
{
	deleteAll(hcTree->root);
}

void deleteAll(HCNODE* hcNode)
{
	if(0 == hcNode) return;
	deleteAll(hcNode->c0);
	deleteAll(hcNode->c1);
	free(hcNode);
}
/*{
	clearerr()
		while(!feof(File *)
		{
			fread(1 byte)
		}
}*/

void initQueue(QUEUE* queue)
{
	queue->numElements = 0;
	queue->head = 0;
}

int size(QUEUE* queue)
{
	return queue->numElements;
}

HCNODE* pop(QUEUE* queue)
{
	HCNODE* tmp;
	HCNODE* highestPriority;
	if(queue->size && queue->head)
	{
		for(tmp = queue->head, highestPriority = queue->head; \
				tmp; tmp=tmp->c1)
		{
			highestPriority = hasGreaterPriority(tmp, highestPriority);
		}

		highestPriority->parent->c1 = highestPriority->c1;
		highestPriority->c1->parent = highestPriority->parent;
		queue->numElements--;
	}
	else
	{
		perror("tried to pop from empty queue");
		exit(EXIT_FAILURE);
	}
	return highestPriority;
}

void push(QUEUE* queue, HCNODE* hcNode)
{
	if(queue->head)
	{
		HCNODE* cursor = queue->head;
		for(cursor = queue->head; cursor->c1 ;cursor = cursor->c1);
		hcNode->parent = cursor;
		cursor->c1 = hcNode;
	}
	else
	{
		queue->head = hcNode;
	}
	queue->numElements++;
}

void deleteQueue(QUEUE* queue)
{
	register HCNODE* tmp;
	while(queue->head)
	{
		tmp = queue->head;
		queue->head = queue->head->c1;
		free(tmp);
	}
	queue->numElements = 0;
}
